#define ARDUINO_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

class StepperMotor {
  public:
    StepperMotor(int In1, int In2, int In3, int In4);
    void setStepDuration(int durata);
    void step (int numarPasi);
    int durata;
    int inputPins[4];
};

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
      for(int inputCount = 0; inputCount < 4; inputCount++) {
        digitalWrite(this->inputPins[inputCount], sequence[(int)(3.5 - (3.5 * factor) + (factor * position))][inputCount]);
      }
    }
  }
}
StepperMotor motor(10, 11, 12, 13);

void setup() {
  Serial.begin(9600);
  motor.setStepDuration(1);
}

void loop() {
  motor.step(100);
  delay(2000);
  motor.step(-100);
  delay(2000);
}
