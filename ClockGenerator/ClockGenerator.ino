// External Clock Generator for AT89S52
// Generates ~4MHz clock on Pin 9 using Timer1
// Connect Arduino Pin 9 → AT89S52 Pin 19 (XTAL1)
// Remove crystal from AT89S52!

void setup() {
  // Configure Pin 9 (OC1A) to output PWM from Timer1
  pinMode(9, OUTPUT);
  
  // Fast PWM mode, no prescaling, 50% duty cycle
  // This generates approximately 4MHz square wave
  TCCR1A = _BV(COM1A0);              // Toggle OC1A on compare match
  TCCR1B = _BV(WGM12) | _BV(CS10);   // CTC mode, no prescaling
  OCR1A = 1;                          // Divide by 2 (16MHz/2 = 8MHz, toggle = 4MHz)
  TCNT1 = 0;
  
  // Clock is now running on Pin 9
  // This sketch does nothing else - just generates clock
}

void loop() {
  // Clock runs automatically via hardware timer
  // Blink LED to show sketch is running
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}
