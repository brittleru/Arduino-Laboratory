#include <Encoder.h>
Encoder myEncoder(2, 3);
float value;
int enA = 10;
int in1 = 9;
int in2 = 8;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  digitalWrite(enA, HIGH);
  Serial.println("..... INAINTE......");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);
  delay(100);
  
  value = myEncoder.read();
  Serial.println(".....valoarea inainte ....");
  Serial.println(value);
  myEncoder.write(0);
  delay(100);
  
  //==================================
  
  Serial.println("..... INAPOI......");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 200);
  delay(100);
  
  value = myEncoder.read();
  Serial.println("....valoarea inapoi......");
  Serial.println(value);
  myEncoder.write(0);
  delay(100);
  
  //==================================
  
  Serial.println("..... SE OPRESTE ......");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  value = myEncoder.read();
  
  Serial.println("....valoarea la oprire......");
  Serial.println(value);
  myEncoder.write(0);
  delay(100); 
}
