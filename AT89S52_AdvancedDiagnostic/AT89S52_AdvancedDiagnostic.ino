// AT89S52 Advanced Diagnostic - Pin-by-Pin Testing
// Tests each connection individually to isolate the problem

#define RESET_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13
#define LED_PIN 13

int testsPassed = 0;
int testsFailed = 0;

void setup() {
  Serial.begin(19200);
  delay(100);
  
  Serial.println("\n\n╔════════════════════════════════════════╗");
  Serial.println("║  AT89S52 ADVANCED DIAGNOSTIC TEST     ║");
  Serial.println("║  Pin-by-Pin Connection Verification   ║");
  Serial.println("╚════════════════════════════════════════╝\n");
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  // Test 1: Individual Pin Readings
  testPinReadings();
  
  // Test 2: Loopback Test (if possible)
  testLoopback();
  
  // Test 3: Reset Pin Control
  testResetControl();
  
  // Test 4: Detailed SPI Communication
  testDetailedSPI();
  
  // Test 5: Alternative Programming Entry
  testAlternativeProgramming();
  
  // Test 6: Clock Detection (indirect)
  testClockDetection();
  
  // Summary
  printSummary();
  
  digitalWrite(LED_PIN, LOW);
}

void testPinReadings() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("TEST 1: Pin State Analysis");
  Serial.println("═══════════════════════════════════════");
  
  pinMode(MOSI_PIN, INPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(SCK_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);
  
  delay(50);
  
  Serial.println("Reading all pins in INPUT mode (floating):");
  int mosi_float = digitalRead(MOSI_PIN);
  int miso_float = digitalRead(MISO_PIN);
  int sck_float = digitalRead(SCK_PIN);
  int reset_float = digitalRead(RESET_PIN);
  
  Serial.print("  MOSI (Pin 11): "); Serial.println(mosi_float ? "HIGH" : "LOW");
  Serial.print("  MISO (Pin 12): "); Serial.println(miso_float ? "HIGH" : "LOW");
  Serial.print("  SCK  (Pin 13): "); Serial.println(sck_float ? "HIGH" : "LOW");
  Serial.print("  RST  (Pin 10): "); Serial.println(reset_float ? "HIGH" : "LOW");
  
  Serial.println("\nSetting pins to OUTPUT LOW:");
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  
  digitalWrite(MOSI_PIN, LOW);
  digitalWrite(SCK_PIN, LOW);
  digitalWrite(RESET_PIN, LOW);
  delay(10);
  
  int miso_with_low = digitalRead(MISO_PIN);
  Serial.print("  MISO reads: "); Serial.println(miso_with_low ? "HIGH" : "LOW");
  
  if (miso_with_low == LOW) {
    Serial.println("  ✓ MISO responds to LOW state");
    testsPassed++;
  } else {
    Serial.println("  ✗ MISO stuck HIGH - check connection or AT89S52 output");
    testsFailed++;
  }
  
  Serial.println("\nSetting RESET HIGH (programming mode):");
  digitalWrite(RESET_PIN, HIGH);
  delay(50);
  
  int miso_prog_mode = digitalRead(MISO_PIN);
  Serial.print("  MISO in prog mode: "); Serial.println(miso_prog_mode ? "HIGH" : "LOW");
  
  Serial.println();
}

void testLoopback() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("TEST 2: Pin Loopback Test");
  Serial.println("═══════════════════════════════════════");
  Serial.println("Temporarily disconnect AT89S52...");
  Serial.println("Connect Arduino Pin 11 (MOSI) to Pin 12 (MISO)");
  Serial.println("Press any key in serial monitor to continue...");
  
  while (!Serial.available()) {
    delay(100);
  }
  while (Serial.available()) Serial.read(); // Clear buffer
  
  Serial.println("\nTesting loopback:");
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  
  bool loopback_works = true;
  
  // Test LOW
  digitalWrite(MOSI_PIN, LOW);
  delay(1);
  if (digitalRead(MISO_PIN) != LOW) {
    Serial.println("  ✗ Loopback failed at LOW");
    loopback_works = false;
  }
  
  // Test HIGH
  digitalWrite(MOSI_PIN, HIGH);
  delay(1);
  if (digitalRead(MISO_PIN) != HIGH) {
    Serial.println("  ✗ Loopback failed at HIGH");
    loopback_works = false;
  }
  
  if (loopback_works) {
    Serial.println("  ✓ Loopback test passed - Arduino pins OK");
    Serial.println("  → Reconnect AT89S52 and continue");
    testsPassed++;
  } else {
    Serial.println("  ✗ Arduino pins may have hardware issue");
    testsFailed++;
  }
  
  Serial.println("\nPress any key when AT89S52 is reconnected...");
  while (!Serial.available()) {
    delay(100);
  }
  while (Serial.available()) Serial.read();
  Serial.println();
}

void testResetControl() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("TEST 3: Reset Line Control Test");
  Serial.println("═══════════════════════════════════════");
  
  pinMode(RESET_PIN, OUTPUT);
  
  Serial.println("Cycling RESET pin 5 times:");
  for (int i = 0; i < 5; i++) {
    digitalWrite(RESET_PIN, LOW);
    delay(100);
    Serial.print("  Cycle "); Serial.print(i + 1); Serial.print(": LOW  ");
    
    digitalWrite(RESET_PIN, HIGH);
    delay(100);
    Serial.println("→ HIGH");
  }
  
  Serial.println("  ✓ Reset cycling complete");
  testsPassed++;
  Serial.println();
}

void testDetailedSPI() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("TEST 4: Detailed SPI Communication");
  Serial.println("═══════════════════════════════════════");
  
  // Enter programming mode
  digitalWrite(RESET_PIN, HIGH);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  
  digitalWrite(SCK_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  delay(20);
  
  digitalWrite(RESET_PIN, LOW);
  delayMicroseconds(100);
  digitalWrite(RESET_PIN, HIGH);
  delay(50);
  
  Serial.println("Sending Programming Enable (0xAC 0x53 0x00 0x00):");
  Serial.println("Byte-by-byte analysis:\n");
  
  byte cmd[] = {0xAC, 0x53, 0x00, 0x00};
  byte response[4];
  
  for (int b = 0; b < 4; b++) {
    Serial.print("  Byte "); Serial.print(b); Serial.print(" (0x");
    if (cmd[b] < 16) Serial.print("0");
    Serial.print(cmd[b], HEX); Serial.print("): ");
    
    response[b] = spiTransferDebug(cmd[b]);
    
    Serial.print("← 0x");
    if (response[b] < 16) Serial.print("0");
    Serial.print(response[b], HEX);
    Serial.print(" ("); Serial.print(response[b], BIN); Serial.println(")");
  }
  
  Serial.println("\nAnalysis:");
  if (response[2] == 0x53) {
    Serial.println("  ✓✓✓ PROGRAMMING ENABLE SUCCESSFUL!");
    Serial.println("  → AT89S52 is responding correctly");
    Serial.println("  → Clock is running");
    Serial.println("  → All connections are good");
    testsPassed += 3;
  } else if (response[0] == 0xFF && response[1] == 0xFF && 
             response[2] == 0xFF && response[3] == 0xFF) {
    Serial.println("  ✗ All 0xFF - MISO line issue:");
    Serial.println("    • MISO not connected to AT89S52 Pin 7");
    Serial.println("    • Or AT89S52 not driving MISO");
    testsFailed++;
  } else if (response[0] == 0x00 && response[1] == 0x00 && 
             response[2] == 0x00 && response[3] == 0x00) {
    Serial.println("  ✗ All 0x00 - Possible issues:");
    Serial.println("    • MISO shorted to ground");
    Serial.println("    • AT89S52 not in programming mode");
    testsFailed++;
  } else {
    Serial.println("  ⚠ Unexpected response - Possible issues:");
    Serial.println("    • AT89S52 clock not running");
    Serial.println("    • Check 12MHz crystal connections");
    Serial.println("    • Check crystal capacitors (22pF)");
    Serial.println("    • Crystal might be faulty");
    testsFailed++;
  }
  
  digitalWrite(RESET_PIN, LOW);
  Serial.println();
}

byte spiTransferDebug(byte data) {
  byte received = 0;
  
  for (int i = 7; i >= 0; i--) {
    // Set MOSI
    digitalWrite(MOSI_PIN, (data >> i) & 0x01);
    delayMicroseconds(2);
    
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

void testAlternativeProgramming() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("TEST 5: Alternative Programming Sequence");
  Serial.println("═══════════════════════════════════════");
  
  Serial.println("Trying different reset timing...");
  
  // Method 1: Longer delays
  pinMode(RESET_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  
  digitalWrite(SCK_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  
  digitalWrite(RESET_PIN, HIGH);
  delay(100);
  
  byte resp1 = spiTransferDebug(0xAC);
  byte resp2 = spiTransferDebug(0x53);
  byte resp3 = spiTransferDebug(0x00);
  byte resp4 = spiTransferDebug(0x00);
  
  Serial.print("  Response: 0x");
  printHex(resp1); Serial.print(" 0x");
  printHex(resp2); Serial.print(" 0x");
  printHex(resp3); Serial.print(" 0x");
  printHex(resp4); Serial.println();
  
  if (resp3 == 0x53) {
    Serial.println("  ✓ Success with longer delays!");
    testsPassed++;
  } else {
    Serial.println("  ✗ Still no response");
    testsFailed++;
  }
  
  digitalWrite(RESET_PIN, LOW);
  Serial.println();
}

void testClockDetection() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("TEST 6: Indirect Clock Detection");
  Serial.println("═══════════════════════════════════════");
  
  Serial.println("Checking if AT89S52 shows signs of life:");
  Serial.println("(Random data suggests clock is running)\n");
  
  digitalWrite(RESET_PIN, HIGH);
  delay(50);
  
  // Read signature multiple times
  byte signatures[3][3];
  bool allSame = true;
  
  for (int attempt = 0; attempt < 3; attempt++) {
    Serial.print("  Attempt "); Serial.print(attempt + 1); Serial.print(": ");
    
    // Enable programming
    spiTransferDebug(0xAC);
    spiTransferDebug(0x53);
    spiTransferDebug(0x00);
    spiTransferDebug(0x00);
    delay(10);
    
    // Read signature bytes
    for (int i = 0; i < 3; i++) {
      spiTransferDebug(0x30);
      spiTransferDebug(0x00);
      spiTransferDebug(i);
      signatures[attempt][i] = spiTransferDebug(0x00);
      delay(5);
    }
    
    Serial.print("0x");
    printHex(signatures[attempt][0]);
    Serial.print(" 0x");
    printHex(signatures[attempt][1]);
    Serial.print(" 0x");
    printHex(signatures[attempt][2]);
    Serial.println();
    
    if (attempt > 0) {
      if (signatures[attempt][0] != signatures[0][0] ||
          signatures[attempt][1] != signatures[0][1] ||
          signatures[attempt][2] != signatures[0][2]) {
        allSame = false;
      }
    }
  }
  
  Serial.println("\nAnalysis:");
  if (signatures[0][0] == 0x1E && signatures[0][1] == 0x52 && signatures[0][2] == 0x06) {
    Serial.println("  ✓✓✓ CORRECT SIGNATURE DETECTED!");
    Serial.println("  → Everything is working perfectly!");
    testsPassed++;
  } else if (allSame && signatures[0][0] == 0xFF) {
    Serial.println("  ✗ Consistent 0xFF - MISO connection problem");
    testsFailed++;
  } else if (allSame && signatures[0][0] == 0x00) {
    Serial.println("  ✗ Consistent 0x00 - Check MISO/GND short");
    testsFailed++;
  } else if (!allSame) {
    Serial.println("  ⚠ Inconsistent readings - Possible issues:");
    Serial.println("    • Clock is unstable or not running");
    Serial.println("    • Check crystal solder joints");
    Serial.println("    • Verify 22pF capacitors are connected");
    Serial.println("    • Crystal might be damaged");
    testsFailed++;
  } else {
    Serial.println("  ⚠ Unexpected but consistent signature");
    Serial.println("    • Wrong chip model?");
    Serial.println("    • Check chip markings");
    testsFailed++;
  }
  
  digitalWrite(RESET_PIN, LOW);
  Serial.println();
}

void printHex(byte b) {
  if (b < 16) Serial.print("0");
  Serial.print(b, HEX);
}

void printSummary() {
  Serial.println("═══════════════════════════════════════");
  Serial.println("DIAGNOSTIC SUMMARY");
  Serial.println("═══════════════════════════════════════");
  Serial.print("Tests Passed: "); Serial.println(testsPassed);
  Serial.print("Tests Failed: "); Serial.println(testsFailed);
  Serial.println();
  
  if (testsPassed >= 5) {
    Serial.println("✓ AT89S52 communication is WORKING!");
    Serial.println("  You can proceed with programming.");
  } else if (testsFailed > 0) {
    Serial.println("✗ Issues detected. Check above for details.");
    Serial.println("\nMost Common Problems:");
    Serial.println("  1. Clock: Verify 12MHz crystal is soldered correctly");
    Serial.println("  2. Capacitors: Check 22pF caps from XTAL pins to GND");
    Serial.println("  3. MISO: Verify Pin 12 → AT89S52 Pin 7 (P1.6)");
    Serial.println("  4. Power: Ensure Pin 40 has 5V, Pin 20 is GND");
    Serial.println("  5. RESET: Verify Pin 10 → AT89S52 Pin 9");
  }
  
  Serial.println("\n═══════════════════════════════════════\n");
}

void loop() {
  // Blink pattern based on results
  if (testsPassed >= 5) {
    // Fast blink - success
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  } else {
    // Slow blink - problems
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}
