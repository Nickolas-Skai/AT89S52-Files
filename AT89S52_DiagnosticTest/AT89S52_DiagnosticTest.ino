// AT89S52 Diagnostic Test Sketch
// Tests power, clock, and SPI communication
// Upload this to Arduino to diagnose AT89S52 connection issues

#define RESET_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13
#define LED_PIN 13  // Built-in LED

int blinkPattern = 1000;  // Default slow blink

void setup() {
  Serial.begin(19200);
  Serial.println("\n\n=== AT89S52 Diagnostic Test ===");
  Serial.println("Testing hardware connections...\n");
  
  // Setup pins
  pinMode(RESET_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  delay(100);
  
  // Test 1: Pin State Test
  Serial.println("TEST 1: Pin State Check");
  Serial.println("------------------------");
  testPinStates();
  
  delay(500);
  
  // Test 2: Reset Signal Test
  Serial.println("\nTEST 2: Reset Signal Test");
  Serial.println("------------------------");
  testResetSignal();
  
  delay(500);
  
  // Test 3: SPI Clock Test
  Serial.println("\nTEST 3: SPI Clock Test");
  Serial.println("------------------------");
  testSPIClock();
  
  delay(500);
  
  // Test 4: AT89S52 Programming Mode Entry
  Serial.println("\nTEST 4: Programming Mode Entry");
  Serial.println("------------------------");
  testProgrammingMode();
  
  delay(500);
  
  // Test 5: Signature Read Attempt
  Serial.println("\nTEST 5: Signature Read");
  Serial.println("------------------------");
  testSignatureRead();
  
  Serial.println("\n=== Diagnostic Complete ===");
  Serial.println("\nLED will blink based on results:");
  Serial.println("- Rapid blink (100ms): Communication OK");
  Serial.println("- Slow blink (1000ms): Check connections");
  Serial.println("- Very slow (2000ms): No response from chip");
}

void testPinStates() {
  // Set all pins to known state
  digitalWrite(RESET_PIN, LOW);
  digitalWrite(SCK_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  delay(10);
  
  int misoState = digitalRead(MISO_PIN);
  
  Serial.print("MISO (Pin 12) reads: ");
  Serial.println(misoState == HIGH ? "HIGH" : "LOW");
  
  if (misoState == LOW) {
    Serial.println("✓ MISO is LOW (expected when idle)");
  } else {
    Serial.println("⚠ MISO is HIGH - check if pin is floating");
  }
}

void testResetSignal() {
  Serial.println("Pulsing RESET pin (Pin 10)...");
  
  // AT89S52 uses active HIGH reset
  digitalWrite(RESET_PIN, LOW);
  delay(10);
  Serial.println("RESET = LOW (normal operation)");
  
  digitalWrite(RESET_PIN, HIGH);
  delay(10);
  Serial.println("RESET = HIGH (reset asserted)");
  
  digitalWrite(RESET_PIN, LOW);
  delay(10);
  Serial.println("RESET = LOW (released)");
  
  Serial.println("✓ Reset pulse complete");
}

void testSPIClock() {
  Serial.println("Generating SCK pulses...");
  
  digitalWrite(SCK_PIN, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(10);
  }
  
  Serial.println("✓ SCK pulse test complete");
  Serial.println("(Use oscilloscope to verify clock on Pin 13)");
}

void testProgrammingMode() {
  Serial.println("Attempting to enter programming mode...");
  
  // Standard AT89S52 programming entry sequence
  digitalWrite(RESET_PIN, HIGH);  // Assert reset (active HIGH for 8051)
  pinMode(RESET_PIN, OUTPUT);
  
  digitalWrite(SCK_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  
  delay(20);
  
  // Release reset to enter programming mode
  digitalWrite(RESET_PIN, LOW);
  delayMicroseconds(100);
  digitalWrite(RESET_PIN, HIGH);  // Programming mode (HIGH)
  
  delay(50);
  
  Serial.println("Programming mode sequence sent");
  Serial.println("RESET should be HIGH during programming");
}

byte spiTransfer(byte data) {
  byte received = 0;
  
  for (int i = 7; i >= 0; i--) {
    // Set MOSI
    digitalWrite(MOSI_PIN, (data >> i) & 0x01);
    
    // Clock HIGH
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(5);
    
    // Read MISO
    if (digitalRead(MISO_PIN)) {
      received |= (1 << i);
    }
    
    // Clock LOW
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(5);
  }
  
  return received;
}

void testSignatureRead() {
  Serial.println("Sending Programming Enable command...");
  
  // Programming Enable: 0xAC 0x53 0x00 0x00
  // Should return 0x53 in third byte if successful
  byte response1 = spiTransfer(0xAC);
  byte response2 = spiTransfer(0x53);
  byte response3 = spiTransfer(0x00);
  byte response4 = spiTransfer(0x00);
  
  Serial.print("Response: 0x");
  if (response1 < 16) Serial.print("0");
  Serial.print(response1, HEX);
  Serial.print(" 0x");
  if (response2 < 16) Serial.print("0");
  Serial.print(response2, HEX);
  Serial.print(" 0x");
  if (response3 < 16) Serial.print("0");
  Serial.print(response3, HEX);
  Serial.print(" 0x");
  if (response4 < 16) Serial.print("0");
  Serial.println(response4, HEX);
  
  if (response3 == 0x53) {
    Serial.println("✓✓✓ PROGRAMMING ENABLE SUCCESSFUL! ✓✓✓");
    blinkPattern = 100;  // Fast blink
  } else {
    Serial.println("✗ No valid response - check connections");
    blinkPattern = 2000;  // Very slow blink
  }
  
  delay(100);
  
  // Try to read signature bytes
  Serial.println("\nReading Device Signature...");
  
  // Read signature byte 0: 0x30 0x00 0x00 0x00
  spiTransfer(0x30);
  spiTransfer(0x00);
  spiTransfer(0x00);
  byte sig0 = spiTransfer(0x00);
  
  delay(10);
  
  // Read signature byte 1: 0x30 0x00 0x01 0x00
  spiTransfer(0x30);
  spiTransfer(0x00);
  spiTransfer(0x01);
  byte sig1 = spiTransfer(0x00);
  
  delay(10);
  
  // Read signature byte 2: 0x30 0x00 0x02 0x00
  spiTransfer(0x30);
  spiTransfer(0x00);
  spiTransfer(0x02);
  byte sig2 = spiTransfer(0x00);
  
  Serial.print("Signature: 0x");
  if (sig0 < 16) Serial.print("0");
  Serial.print(sig0, HEX);
  Serial.print(" 0x");
  if (sig1 < 16) Serial.print("0");
  Serial.print(sig1, HEX);
  Serial.print(" 0x");
  if (sig2 < 16) Serial.print("0");
  Serial.println(sig2, HEX);
  
  Serial.print("Expected:  0x1E 0x52 0x06 (AT89S52)\n");
  
  if (sig0 == 0x1E && sig1 == 0x52 && sig2 == 0x06) {
    Serial.println("\n✓✓✓ AT89S52 DETECTED! PERFECT! ✓✓✓");
    blinkPattern = 100;  // Fast blink
  } else if (sig0 == 0x00 && sig1 == 0x00 && sig2 == 0x00) {
    Serial.println("\n✗ All zeros - possible issues:");
    Serial.println("  - AT89S52 not powered");
    Serial.println("  - No clock signal to AT89S52");
    Serial.println("  - SPI pins not connected");
    Serial.println("  - AT89S52 not in programming mode");
    blinkPattern = 2000;
  } else if (sig0 == 0xFF && sig1 == 0xFF && sig2 == 0xFF) {
    Serial.println("\n✗ All 0xFF - MISO line issue:");
    Serial.println("  - MISO not connected");
    Serial.println("  - MISO line stuck HIGH");
    blinkPattern = 1500;
  } else {
    Serial.println("\n⚠ Unexpected signature - check chip or connections");
    blinkPattern = 1000;
  }
  
  // Exit programming mode
  digitalWrite(RESET_PIN, LOW);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(blinkPattern);
  digitalWrite(LED_PIN, LOW);
  delay(blinkPattern);
}
