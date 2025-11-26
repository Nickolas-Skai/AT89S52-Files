// AT89S52 Crystal Oscillator Test
// Tests multiple SPI speeds to detect if crystal is oscillating at wrong frequency

#define RESET_PIN 10
#define MOSI_PIN  11
#define MISO_PIN  12
#define SCK_PIN   13

void setup() {
  Serial.begin(19200);
  while (!Serial) ;
  delay(1000);
  
  Serial.println(F("\n=== AT89S52 CRYSTAL OSCILLATOR TEST ===\n"));
  Serial.println(F("Testing different SPI clock speeds..."));
  Serial.println(F("If crystal works at ANY speed, we'll find it!\n"));
  
  pinMode(RESET_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  
  digitalWrite(RESET_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  digitalWrite(SCK_PIN, LOW);
  delay(100);
  
  // Test different clock speeds
  testSpeed("Very Slow (200us)", 200);
  testSpeed("Slow (100us)", 100);
  testSpeed("Medium (50us)", 50);
  testSpeed("Fast (10us)", 10);
  testSpeed("Very Fast (2us)", 2);
  testSpeed("Ultra Fast (1us)", 1);
  
  Serial.println(F("\n=== TEST COMPLETE ==="));
  Serial.println(F("\nIf ALL tests show wrong signature:"));
  Serial.println(F("→ Crystal is NOT oscillating"));
  Serial.println(F("→ Check crystal solder joints on pins 18 & 19"));
  Serial.println(F("→ Try different crystal"));
  Serial.println(F("→ Add 22pF capacitors (NOT 20µF!)"));
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(500);
}

void testSpeed(const char* name, int delayUs) {
  Serial.print(F("\nTest: "));
  Serial.println(name);
  
  // Reset and enter programming mode
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);
  delay(50);
  
  // Try programming enable
  byte r3 = 0;
  spiTransfer(0xAC, delayUs);
  spiTransfer(0x53, delayUs);
  r3 = spiTransfer(0x00, delayUs);
  spiTransfer(0x00, delayUs);
  
  Serial.print(F("  Programming Enable: "));
  if (r3 == 0x53) {
    Serial.println(F("✓ SUCCESS"));
  } else {
    Serial.print(F("✗ Failed (got 0x"));
    Serial.print(r3, HEX);
    Serial.println(F(")"));
  }
  
  // Read signature
  Serial.print(F("  Signature: "));
  byte sig[3];
  for (int i = 0; i < 3; i++) {
    spiTransfer(0x30, delayUs);
    spiTransfer(0x00, delayUs);
    spiTransfer(i, delayUs);
    sig[i] = spiTransfer(0x00, delayUs);
    
    if (sig[i] < 16) Serial.print('0');
    Serial.print(sig[i], HEX);
    Serial.print(' ');
  }
  
  if (sig[0] == 0x1E && sig[1] == 0x52 && sig[2] == 0x06) {
    Serial.println(F("✓✓✓ CORRECT! Crystal is working at this speed!"));
  } else if (sig[0] == 0xFF && sig[1] == 0xFF && sig[2] == 0xFF) {
    Serial.println(F("(all 0xFF - no response)"));
  } else if (sig[0] == 0x00 && sig[1] == 0x00 && sig[2] == 0x00) {
    Serial.println(F("(all 0x00 - no response)"));
  } else {
    Serial.println(F("✗ Wrong signature"));
  }
  
  digitalWrite(RESET_PIN, LOW);
  delay(100);
}

byte spiTransfer(byte data, int delayUs) {
  byte result = 0;
  
  for (int i = 7; i >= 0; i--) {
    // Set MOSI bit
    digitalWrite(MOSI_PIN, (data >> i) & 1);
    delayMicroseconds(delayUs);
    
    // Clock HIGH and read MISO
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(delayUs);
    result = (result << 1) | digitalRead(MISO_PIN);
    
    // Clock LOW
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(delayUs);
  }
  
  return result;
}
