#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define MS3 6
#define EN 7

char userInput;
int x;
int y;
int state;


void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);
  resetBEDPins();

  Serial.begin(9600);
  Serial.println("Begin motor control");
  Serial.println();
  Serial.println("Introduceti numarul dorit: ");
  Serial.println("1. Miscare cu pasul motorului");
  Serial.println("2. Miscare inversa cu micropasire");
  Serial.println("3. Miscare cu micropasire 1/16 din pas");
  Serial.println("4. Miscare inainte si inapoi");
  Serial.println();
}

void loop() {
  while(Serial.available()) {
    userInput = Serial.read();
    digitalWrite(EN, LOW); //Poate fi comandat doar pe LOW
    if (userInput == '1') {
      StepForwardDefault();
    }
    else if (userInput = '2') {
      ReverseStepDefault();
    }
    else if (userInput = '3') {
      SmallStepMode();
    }
    else if (userInput = '4') {
      ForwardBackwardStep();
    }
    else {
      Serial.println("Nu ati introdus un numar valabil! Va rog introduceti un numar din optiunile valabile!");
    }
    resetBEDPins();
     
  }
}

void resetBEDPins() {
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH); // se opreste comanda 
}

void StepForwardDefault() {
  Serial.println("Miscare inainte cu pasul motorului.");
  digitalWrite(dir, LOW);
  for (x = 1; x < 1000; x++) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
  }
  Serial.println("Introduceti o noua optiune...");
  Serial.println();
}

void ReverseStepDefault() {
  Serial.println("Miscare inversa cu valoarea pasului");
  digitalWrite(dir, HIGH);
  for (x = 1; x < 1000; ++x) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
  }
  Serial.println("Introduceti o noua optiune...");
  Serial.println();
}

void SmallStepMode() {
  Serial.println("Miscare 1/16 micropasire.");
  digitalWrite(dir, LOW);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (x = 1; x < 1000; x++) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
  }
  Serial.println("Introduceti o noua optiune...");
  Serial.println();
}

void ForwardBackwardStep() {
  Serial.println("Miscare inainte si inapoi");
  for (x = 1; x < 250; x++) {
    state = digitalRead(dir);
    if (state == HIGH) {
      digitalWrite(dir, LOW);
    }
    else if (state == LOW) {
      digitalWrite(dir, HIGH);
    }
    for (y = 1; y < 250; y++) {
      digitalWrite(stp, HIGH);
      delay(100);
      digitalWrite(stp, LOW);
      delay(100);
    }
  }
  Serial.println("Introduceti o noua optiune...");
  Serial.println();
}













// Senzor infra rosu
//int valoareSenzor = 0;
//int pinInfrarosu = 0;

//void setup() {
//  Serial.begin(9600);
//}
//
//void loop() {
//  valoareSenzor = analogRead(pinInfrarosu);
//  Serial.println(valoareSenzor);
//  float dist = map(valoareSenzor, 10, 400, 10, 80);
//  Serial.println(dist);
//  delay(400);
//}

// ---------------------------- //

//void setup() {
//  Serial.begin(9600);
//}
//
//void loop() {
//  int valoareSenzor = readDistanceMediata(10, 0);
//  Serial.print("Valoare senzor: ");
//  Serial.print(valoareSenzor);
//  delay(100);  
//}
//
//int readDistanceMediata(int count, int pin) {
//  int sum = 0;
//  int i;
//  float volts;
//  for (i = 0; i < count; i++) {
//    float volts = analogRead(pin) * ((float)5 / 1024); 
//    float distance = 65 * pow(volts, -1.10);
//    sum += distance;
//    delay(5);  
//  }
//  return (int)(sum / count);
//}










// Senzor de forta
//void setup() {
//  Serial.begin(9600);
//}
//
//void loop() {
//  int val = analogRead(0);
//  if (val > 0) {
//    Serial.print("Nivel de apasare: ");
//    Serial.print(val);
//    Serial.println();
//    delay(100);
//  }
//}
//
//








//
