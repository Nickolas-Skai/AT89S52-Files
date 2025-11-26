// Final Comprehensive AT89S52 Diagnostic
// Tests all connections systematically

#define RESET_PIN 10
#define MOSI_PIN  11
#define MISO_PIN  12
#define SCK_PIN   13
#define CLOCK_OUT 9

void setup() {
  Serial.begin(19200);
  while (!Serial);
  delay(1000);
  
  Serial.println(F("\n╔═══════════════════════════════════════╗"));
  Serial.println(F("║  AT89S52 FINAL DIAGNOSTIC TEST       ║"));
  Serial.println(F("╚═══════════════════════════════════════╝\n"));
  
  pinMode(RESET_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(CLOCK_OUT, OUTPUT);
  
  // Start clock generation
  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1A = 3;  // 2MHz
  TCNT1 = 0;
  
  Serial.println(F("Clock generator started on Pin 9 (2MHz)"));
  Serial.println(F("Connect: Arduino Pin 9 → AT89S52 Pin 19\n"));
  
  delay(100);
  
  test1_PowerCheck();
  test2_PinStates();
  test3_MISOResponse();
  test4_ProgrammingAttempt();
  test5_DifferentTimings();
  
  Serial.println(F("\n╔═══════════════════════════════════════╗"));
  Serial.println(F("║  DIAGNOSTIC COMPLETE                  ║"));
  Serial.println(F("╚═══════════════════════════════════════╝\n"));
  
  printConclusion();
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(1000);
}

void test1_PowerCheck() {
  Serial.println(F("TEST 1: Power Rails"));
  Serial.println(F("  Use multimeter to verify:"));
  Serial.println(F("  - AT89S52 Pin 40 (VCC) = 5V"));
  Serial.println(F("  - AT89S52 Pin 20 (GND) = 0V"));
  Serial.println(F("  - AT89S52 Pin 31 (EA) = 5V"));
  Serial.println(F("  Type 'OK' when verified..."));
  
  waitForOK();
}

void test2_PinStates() {
  Serial.println(F("\nTEST 2: Pin State Analysis"));
  
  digitalWrite(RESET_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  digitalWrite(SCK_PIN, LOW);
  delay(50);
  
  Serial.print(F("  RESET LOW → MISO: "));
  Serial.println(digitalRead(MISO_PIN) ? "HIGH" : "LOW");
  
  digitalWrite(RESET_PIN, HIGH);
  delay(20);
  
  Serial.print(F("  RESET HIGH → MISO: "));
  int miso = digitalRead(MISO_PIN);
  Serial.println(miso ? "HIGH" : "LOW");
  
  if (miso == HIGH) {
    Serial.println(F("  ⚠ MISO stays HIGH (floating or disconnected)"));
  } else {
    Serial.println(F("  ✓ MISO responds to RESET"));
  }
  
  digitalWrite(RESET_PIN, LOW);
}

void test3_MISOResponse() {
  Serial.println(F("\nTEST 3: MISO Connection Verify"));
  Serial.println(F("  Disconnect MISO from AT89S52"));
  Serial.println(F("  Touch MISO wire to GND"));
  Serial.println(F("  Type 'OK' when ready..."));
  
  waitForOK();
  
  if (digitalRead(MISO_PIN) == LOW) {
    Serial.println(F("  ✓ MISO reads LOW - Arduino Pin 12 OK"));
  } else {
    Serial.println(F("  ✗ MISO still HIGH - Check Arduino Pin 12!"));
  }
  
  Serial.println(F("  Reconnect MISO to AT89S52 Pin 7"));
  Serial.println(F("  Type 'OK'..."));
  waitForOK();
}

void test4_ProgrammingAttempt() {
  Serial.println(F("\nTEST 4: Programming Enable Sequence"));
  
  digitalWrite(RESET_PIN, HIGH);
  delay(50);
  
  Serial.println(F("  Sending: AC 53 00 00"));
  byte r[4];
  r[0] = xfer(0xAC);
  r[1] = xfer(0x53);
  r[2] = xfer(0x00);
  r[3] = xfer(0x00);
  
  Serial.print(F("  Received: "));
  printHex(r, 4);
  
  if (r[2] == 0x53) {
    Serial.println(F(" ✓✓ SUCCESS!"));
  } else {
    Serial.print(F(" ✗ Expected 3rd byte=0x53, got 0x"));
    Serial.println(r[2], HEX);
  }
  
  // Read signature
  Serial.println(F("\n  Reading Device Signature:"));
  byte sig[3];
  for (int i = 0; i < 3; i++) {
    xfer(0x30);
    xfer(0x00);
    xfer(i);
    sig[i] = xfer(0x00);
  }
  
  Serial.print(F("  Signature: "));
  printHex(sig, 3);
  
  if (sig[0] == 0x1E && sig[1] == 0x52 && sig[2] == 0x06) {
    Serial.println(F(" ✓✓✓ CORRECT AT89S52!"));
  } else if (sig[0] == 0x00 && sig[1] == 0x00 && sig[2] == 0x00) {
    Serial.println(F(" ✗ All zeros - No communication"));
  } else if (sig[0] == 0xFF) {
    Serial.println(F(" ✗ All 0xFF - MISO floating/disconnected"));
  } else {
    Serial.println(F(" ✗ Wrong signature"));
  }
  
  digitalWrite(RESET_PIN, LOW);
}

void test5_DifferentTimings() {
  Serial.println(F("\nTEST 5: Try Different SPI Speeds"));
  
  int delays[] = {1, 5, 10, 50, 100};
  
  for (int d = 0; d < 5; d++) {
    digitalWrite(RESET_PIN, HIGH);
    delay(50);
    
    byte r3 = 0;
    xferSlow(0xAC, delays[d]);
    xferSlow(0x53, delays[d]);
    r3 = xferSlow(0x00, delays[d]);
    xferSlow(0x00, delays[d]);
    
    Serial.print(F("  Delay="));
    Serial.print(delays[d]);
    Serial.print(F("us → 0x"));
    Serial.print(r3, HEX);
    
    if (r3 == 0x53) {
      Serial.println(F(" ✓ WORKS!"));
    } else {
      Serial.println();
    }
    
    digitalWrite(RESET_PIN, LOW);
    delay(100);
  }
}

void printConclusion() {
  Serial.println(F("CONCLUSION:"));
  Serial.println(F(""));
  Serial.println(F("If ALL tests show 0x00 or 0xFF signatures:"));
  Serial.println(F("  1. Clock not reaching AT89S52 Pin 19"));
  Serial.println(F("  2. AT89S52 chip is faulty/counterfeit"));
  Serial.println(F("  3. MISO not connected to Pin 7"));
  Serial.println(F(""));
  Serial.println(F("Next Steps:"));
  Serial.println(F("  • Verify Pin 9 → Pin 19 continuity with multimeter"));
  Serial.println(F("  • Check AT89S52 chip isn't damaged"));
  Serial.println(F("  • Try different AT89S52 chip if available"));
  Serial.println(F("  • Get 22pF capacitors and use real crystal"));
}

byte xfer(byte data) {
  byte result = 0;
  for (int i = 7; i >= 0; i--) {
    digitalWrite(MOSI_PIN, (data >> i) & 1);
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(2);
    result = (result << 1) | digitalRead(MISO_PIN);
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(2);
  }
  return result;
}

byte xferSlow(byte data, int delayUs) {
  byte result = 0;
  for (int i = 7; i >= 0; i--) {
    digitalWrite(MOSI_PIN, (data >> i) & 1);
    delayMicroseconds(delayUs);
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(delayUs);
    result = (result << 1) | digitalRead(MISO_PIN);
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(delayUs);
  }
  return result;
}

void printHex(byte* data, int len) {
  for (int i = 0; i < len; i++) {
    if (data[i] < 16) Serial.print('0');
    Serial.print(data[i], HEX);
    Serial.print(' ');
  }
}

void waitForOK() {
  while (!Serial.available()) {
    delay(100);
  }
  while (Serial.available()) Serial.read();
}
