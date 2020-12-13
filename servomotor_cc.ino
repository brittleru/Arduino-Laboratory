#include <Servo.h>
Servo motor1;
const int servopin = 9;
const int potentiometru = A3;
int unghi;
int valoare = 0;
int citire_pot;

void setup() {
  Serial.begin(9600);
  motor1.attach(servopin, 544, 2400);
}

void loop() {
  
//  citire_pot = analogRead(potentiometru);
//  analogWrite(servopin, citire_pot / 4); // valori analogRead valori de la 0 la 1023,
//  analogWrite valori de la 0 la 255
  
  for (int i = 0; i <= 4; i++){
    //........unu......ZERO
    motor1.write(valoare);
    delay(1500);
    
    Serial.println("valoarea este ");
    Serial.println(valoare);
    unghi = motor1.read();
    
    Serial.println(unghi);
    Serial.println("....UNU......");
    valoare += 45;
  }
  
  valoare = 180;
  analogWrite(servopin, 255);
  
  for (int i = 0; i <= 4; i++) {
    //........unu......ZERO
    motor1.write(valoare);
    delay(1500);
    
    Serial.println("valoarea este ");
    Serial.println(valoare);
    unghi = motor1.read();
    
    Serial.println(unghi);
    Serial.println("....UNU......");
    valoare -= 45;
  }
}
