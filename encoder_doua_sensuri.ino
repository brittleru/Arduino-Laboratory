int encoder_value;
int enA = 10;
int in1 = 9;
int in2 = 8;
int in_encoder = 2;
void count(void);

void setup() {
   
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in_encoder, INPUT);
  Serial.begin(9600);
  attachInterrupt(2, count, FALLING);
  encoder_value = 0;
}

void loop() {
  
  digitalWrite(enA, HIGH);
  Serial.println("..... INAINTE......");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);
  delay(100);
  
  encoder_value = analogRead(in_encoder);
  Serial.println(".....val cu intrerupere INAINTE....");
  Serial.println(encoder_value);
  delay(100);
  
  //==================================
  
  Serial.println("..... INAPOI......");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 200);
  delay(100);

  //se adauga millis
  encoder_value = analogRead(in_encoder);
  Serial.println(".....val cu intrerupere INAPOI ....");
  Serial.println(encoder_value);
  delay(100);
  
  //==================================

  Serial.println("..... SE OPRESTE 1 SEC......");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  encoder_value = analogRead(in_encoder);
  Serial.println(".....val cu intrerupere OPRIRE ....");
  Serial.println(encoder_value);
  encoder_value = 0;
  delay(100);
}
void count() { 
  encoder_value++;
}
