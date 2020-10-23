unsigned int ecouPin = 13;
unsigned int trigPin = 12;
float durata, distantaCm;

void setup() {
  Serial.begin(9600);
  pinMode(ecouPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Serial.println("Incepe Masurarea");
  durata = pulseIn(ecouPin, HIGH);
  Serial.println("Durata este: ");
  Serial.println(durata);
  {
    distantaCm = durata * 0.0343 / 2;
    if (distantaCm > 400 && distantaCm < 2)
      Serial.println("Distanta masurata este: ");
      Serial.println(distantaCm);
      Serial.println(" cm");
  }
  delayMicroseconds(100);
}
