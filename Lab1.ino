#include<Servo.h>
Servo motor1;
int pozitie1 = 0;
const int SENZOR_PIN = A1; // pin analog1
const int RS = 228; // SI[ohm]
const int TENSIUNE_REF = 5;
float senzorValue;
float current;

void setup() {
  Serial.begin(9600);
  motor1.attach(9);
}

void loop() {
  senzorValue = analogRead(SENZOR_PIN);
  // servo-motor
  Serial.println("Begin...");
  for(pozitie1 = 0; pozitie1 <= 180; pozitie1 += 1) {
    motor1.write(pozitie1);
    delay(20);
  }
  for(pozitie1 = 180; pozitie1 >= 0; pozitie1 -= 1) {
    motor1.write(pozitie1);
    delay(20);
  }
  //  ref 5V reeval value
  senzorValue = (senzorValue * TENSIUNE_REF) / 1023;
  //  10 decimals
  Serial.print(senzorValue, 8);
  Serial.println("B");
  // From INA169 let RL = 10k
  // Is = (Vout x 1k) / (RS x RL)
  current = senzorValue / (10 * RS);
  // current val with 6 decimals in Amper
  Serial.print(current, 6);
  Serial.println(" A");
  delay(500);  
}
