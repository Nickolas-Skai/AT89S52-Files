// Test if Arduino Pin 9 is generating clock signal
// This measures how often Pin 9 changes state

#define CLOCK_PIN 9
#define TEST_PIN 8  // We'll count transitions

volatile unsigned long transitionCount = 0;

void setup() {
  Serial.begin(19200);
  while (!Serial);
  delay(1000);
  
  Serial.println(F("\n=== Clock Output Test ==="));
  Serial.println(F("Checking if Pin 9 generates clock...\n"));
  
  // Setup Timer1 to generate clock on Pin 9
  pinMode(CLOCK_PIN, OUTPUT);
  TCCR1A = _BV(COM1A0);              // Toggle OC1A on compare match
  TCCR1B = _BV(WGM12) | _BV(CS10);   // CTC mode, no prescaling
  OCR1A = 1;                          // Divide by 2
  TCNT1 = 0;
  
  delay(100);
  
  // Count transitions on Pin 9
  pinMode(TEST_PIN, INPUT);
  
  Serial.println(F("Measuring for 1 second..."));
  
  unsigned long startTime = millis();
  int lastState = digitalRead(CLOCK_PIN);
  unsigned long count = 0;
  
  while (millis() - startTime < 1000) {
    int state = digitalRead(CLOCK_PIN);
    if (state != lastState) {
      count++;
      lastState = state;
    }
  }
  
  float frequency = count / 2.0; // Two transitions per cycle
  
  Serial.print(F("Transitions counted: "));
  Serial.println(count);
  Serial.print(F("Estimated frequency: "));
  Serial.print(frequency / 1000.0);
  Serial.println(F(" kHz"));
  
  if (frequency > 100000) {
    Serial.println(F("\n✓ Clock is generating! (~4MHz expected)"));
  } else if (frequency > 1000) {
    Serial.println(F("\n⚠ Clock running but slower than expected"));
  } else {
    Serial.println(F("\n✗ Clock NOT generating"));
  }
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(500);
}
