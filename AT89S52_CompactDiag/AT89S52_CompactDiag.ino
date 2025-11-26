// AT89S52 Compact Diagnostic
#define RESET_PIN 10
#define MOSI_PIN  11
#define MISO_PIN  12
#define SCK_PIN   13

byte sig[5][3];

void setup() {
  Serial.begin(19200);
  while (!Serial) ;
  delay(1000);
  
  Serial.println(F("\n=== AT89S52 DIAGNOSTIC ===\n"));
  
  pinMode(RESET_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  
  digitalWrite(RESET_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  digitalWrite(SCK_PIN, LOW);
  delay(100);
  
  test1_PinStates();
  test2_Programming();
  test3_Consistency();
  test4_SlowClock();
  
  Serial.println(F("\n=== COMPLETE ==="));
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(1000);
}

void test1_PinStates() {
  Serial.println(F("TEST 1: Pin States"));
  Serial.print(F("  MISO idle: "));
  Serial.println(digitalRead(MISO_PIN) ? "HIGH ⚠" : "LOW ✓");
  
  digitalWrite(RESET_PIN, HIGH);
  delay(10);
  Serial.print(F("  MISO active: "));
  Serial.println(digitalRead(MISO_PIN) ? "HIGH" : "LOW");
  digitalWrite(RESET_PIN, LOW);
}

void test2_Programming() {
  Serial.println(F("\nTEST 2: Programming Enable"));
  digitalWrite(RESET_PIN, HIGH);
  delay(20);
  
  byte r[4];
  r[0] = xfer(0xAC);
  r[1] = xfer(0x53);
  r[2] = xfer(0x00);
  r[3] = xfer(0x00);
  
  Serial.print(F("  Sent: AC 53 00 00\n  Recv: "));
  for (int i = 0; i < 4; i++) {
    if (r[i] < 16) Serial.print('0');
    Serial.print(r[i], HEX);
    Serial.print(' ');
  }
  Serial.println(r[2] == 0x53 ? "✓" : "✗");
  
  // Read signature
  Serial.print(F("  Signature: "));
  for (int i = 0; i < 3; i++) {
    xfer(0x30);
    xfer(0x00);
    xfer(i);
    sig[0][i] = xfer(0x00);
    if (sig[0][i] < 16) Serial.print('0');
    Serial.print(sig[0][i], HEX);
    Serial.print(' ');
  }
  if (sig[0][0] == 0x1E && sig[0][1] == 0x52 && sig[0][2] == 0x06)
    Serial.println("✓");
  else if (sig[0][0] == 0xFF)
    Serial.println("⚠ MISO disconnected");
  else
    Serial.println("✗");
  
  digitalWrite(RESET_PIN, LOW);
}

void test3_Consistency() {
  Serial.println(F("\nTEST 3: Consistency (5 reads)"));
  
  for (int a = 0; a < 5; a++) {
    digitalWrite(RESET_PIN, HIGH);
    delay(20);
    xfer(0xAC); xfer(0x53); xfer(0x00); xfer(0x00);
    for (int i = 0; i < 3; i++) {
      xfer(0x30); xfer(0x00); xfer(i);
      sig[a][i] = xfer(0x00);
    }
    digitalWrite(RESET_PIN, LOW);
    delay(50);
    
    Serial.print(F("  #"));
    Serial.print(a + 1);
    Serial.print(F(": "));
    for (int i = 0; i < 3; i++) {
      if (sig[a][i] < 16) Serial.print('0');
      Serial.print(sig[a][i], HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
  
  bool same = true;
  for (int a = 1; a < 5; a++)
    for (int i = 0; i < 3; i++)
      if (sig[a][i] != sig[0][i]) same = false;
  
  Serial.print(F("  Result: "));
  Serial.println(same ? "Consistent ✓" : "Varying ⚠ Clock issue");
}

void test4_SlowClock() {
  Serial.println(F("\nTEST 4: Slow Clock"));
  digitalWrite(RESET_PIN, HIGH);
  delay(50);
  
  byte r3 = 0;
  slowXfer(0xAC);
  slowXfer(0x53);
  r3 = slowXfer(0x00);
  slowXfer(0x00);
  
  Serial.print(F("  3rd byte: 0x"));
  Serial.print(r3, HEX);
  Serial.println(r3 == 0x53 ? " ✓" : " ✗");
  
  digitalWrite(RESET_PIN, LOW);
}

byte xfer(byte d) {
  byte r = 0;
  for (int i = 7; i >= 0; i--) {
    digitalWrite(MOSI_PIN, (d >> i) & 1);
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(1);
    r = (r << 1) | digitalRead(MISO_PIN);
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(1);
  }
  return r;
}

byte slowXfer(byte d) {
  byte r = 0;
  for (int i = 7; i >= 0; i--) {
    digitalWrite(MOSI_PIN, (d >> i) & 1);
    delayMicroseconds(10);
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(50);
    r = (r << 1) | digitalRead(MISO_PIN);
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(50);
  }
  return r;
}
