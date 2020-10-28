// Directiva pentru preprocesare: 
#define ARDUINO_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

// Declararea Variabilelor Globale:
unsigned int ecouPin = 3;
unsigned int trigPin = 2;
float durata, distantaCm;
float nouDistanta;

// Declararea Clasei StepperMotor: date membru -> (durata unui pas si pinii de intrare pentru motor)
class StepperMotor {
  public:
    StepperMotor(int In1, int In2, int In3, int In4);
    void setStepDuration(int durata);
    void step (int numarPasi);
    int durata;
    int inputPins[4];
};

//
StepperMotor::StepperMotor(int In1, int In2, int In3, int In4) {
  this->inputPins[0] = In1;
  this->inputPins[1] = In2;
  this->inputPins[2] = In3;
  this->inputPins[3] = In4;

  for (int inputCount = 0; inputCount < 4; inputCount++) {
    pinMode(this->inputPins[inputCount], OUTPUT);
  }

  durata = 50;
}

void StepperMotor::setStepDuration(int durata) {
  this->durata = durata;
}

void StepperMotor::step(int numarPasi) {
  bool sequence[][4] = { {LOW, LOW, LOW, HIGH},
                         {LOW, LOW, HIGH, HIGH},
                         {LOW, LOW, HIGH, LOW},
                         {LOW, HIGH, HIGH, LOW},
                         {LOW, HIGH, LOW, LOW},
                         {HIGH, HIGH, LOW, LOW},
                         {HIGH, LOW, LOW, LOW},
                         {HIGH, LOW, LOW, HIGH} 
  };
  int factor = abs(numarPasi) / numarPasi;
  numarPasi = abs(numarPasi);

  for (int sequenceNum = 0; sequenceNum <= numarPasi/8; sequenceNum++) {
    for (int position = 0; (position < 8) && (position < (numarPasi - sequenceNum * 8)); position++){
      delay(durata);
      for (int inputCount = 0; inputCount < 4; inputCount++) {
        digitalWrite(this->inputPins[inputCount], sequence[(int)(3.5 - (3.5 * factor) + (factor * position))][inputCount]);
      }
    }
  }
}

// Declararea pinilor pentru cele doua motoare: 
StepperMotor motor1(10, 11, 12, 13);
StepperMotor motor2(4, 5, 6, 7);

// Functie pentru calculul distantei masurate cu senzor ultrasonic:
float functieDistanta(int ecouPin, int trigPin) {
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
    if (distantaCm < 400 && distantaCm > 2)
      Serial.println("Distanta masurata este: ");
      Serial.println(distantaCm);
      Serial.println(" cm");
  }
  delayMicroseconds(100);

  return distantaCm;
}

void setup() {
  Serial.begin(9600);
  motor1.setStepDuration(1);
  motor2.setStepDuration(1);
  pinMode(ecouPin, INPUT);
  pinMode(trigPin, OUTPUT);
  delay(100);
}

void loop() {

  // Merge inainte
  motor1.step(100);
  motor2.step(100);
  delay(2000); 

  nouDistanta = functieDistanta(ecouPin, trigPin);
  Serial.println(nouDistanta); // 100 si 150 cm

  // Conditie pentru distanta in intervalul 100 si 150 cm (interval de siguranta)
  if (nouDistanta > 100 && nouDistanta < 150) {
    
    // Se opreste deoarece senzorul sesizeaza un obstacol
    motor1.step(0);
    motor2.step(0);
    delay(2000);

    // Face o curba ca sa ocoleasca obstacolul
    int raza1 = 100;  // raza interioara milimetri
    int raza2 = 200;  // raza exterioara milimetri
    motor1.step(26);  // roata ineriorul curbei
    motor2.step(48);  // roata exteriorul curbei
    delay(2000);
  }
  else {
    
    // Merge inainte
    motor1.step(100);
    motor2.step(100);
    delay(2000); 
  }

  // Merge inainte
  motor1.step(100);
  motor2.step(100);
  delay(2000); 

  // Merge cu spatele
  motor1.step(-100);
  motor2.step(-100);
  delay(2000);

  // Se opresc ambele motoare
  motor1.step(0);
  motor2.step(0);
  delay(2000);
}
