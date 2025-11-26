// MISO Continuity Test
// This will help verify the MISO connection

#define MISO_PIN 12

void setup() {
  Serial.begin(19200);
  while (!Serial) ;
  delay(1000);
  
  Serial.println(F("\n=== MISO CONNECTION TEST ==="));
  Serial.println(F("\nInstructions:"));
  Serial.println(F("1. Disconnect MISO from AT89S52 Pin 7"));
  Serial.println(F("2. Touch MISO wire to GND (Arduino GND pin)"));
  Serial.println(F("3. Observe if reading changes to LOW"));
  Serial.println();
  
  pinMode(MISO_PIN, INPUT);
}

void loop() {
  int reading = digitalRead(MISO_PIN);
  
  Serial.print(F("MISO (Pin 12): "));
  Serial.print(reading ? "HIGH" : "LOW");
  Serial.print(F("  |  "));
  
  // Also show analog reading for more detail
  int analog = analogRead(MISO_PIN - 12 + 0); // Convert to A0-A5
  Serial.print(F("Analog: "));
  Serial.println(analog);
  
  delay(500);
}
