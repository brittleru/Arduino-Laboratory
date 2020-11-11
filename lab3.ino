#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define MS3 6
#define EN 7

int x;
int y;
int state;
int pinInfrarosu = A0;
int pinForta = A1;

// Actionarea pentru un mecanism de prehensiune (gripper) care trb
// Sa deplaseze un obiect paralelipipedic cu baza 100mm si latimea 100mm
// Inaltimea pp este 300mm, inaltimea maxima a mecanismului este de 400mm
// Avem un senzor infrarosu de ditanta si sezizeaza aproprierea de obiect
// Daca distanta este mai mica de 20 mm atunci trb oprit 
// Modulul de la roata dintata este de 3mm, roata dintata de pe motor are 20 de dinti
// Unghiul motorului este 1.8 grade
// un decaN este un KG forta

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
}

void loop() {
  
//  Deplasare inainte
  digitalWrite(EN, LOW); //Poate fi comandat doar pe LOW
  StepForwardDefault(5);
  resetBEDPins();

//  Testare distanta cu senzor infrarosu 
  float distanta = masurareSenzor(pinInfrarosu);
  if (distanta > 20) {
    // Deplasare cu micropasire pe distanta de 19mm
    digitalWrite(EN, LOW);
    SmallStepMode(4);
    resetBEDPins();
  }
  else {
//    Se Opreste motorul 
    resetBEDPins();
  }


// Testare forta de apasare pe obiect cu senzor de forta
  float val = masurareSenzorForta(pinForta);
  if (val > 350) {
//    Se opreste motorul
    digitalWrite(EN, HIGH);
    resetBEDPins();
  }
  else {
//    Se contiuna cu micropasire 
    int nr_micropasi = 1;
    while(val < 350) {
      SmallStepMode(nr_micropasi);
      nr_micropasi += 1;
    }
    resetBEDPins();
  }
  

// Se opreste motorul de la mecanismul de prehensiune
  

// Se comanda motorul de la mecanismul de orientare pentru un unghi de 90*
  digitalWrite(EN, LOW);
  StepForwardDefault(50);
  resetBEDPins();
  digitalWrite(EN, HIGH);
  

// Desprindere obiect - functia ReverseSetpDefault 
  digitalWrite(EN, LOW);
  float valoare = masurareSenzorForta(pinForta);
  int nr_pasi = 1;
    while(val > 350) {
      ReverseStepDefault(nr_pasi);
      nr_pasi += 1;
    }

//  Oprire
  resetBEDPins();
  digitalWrite(EN, HIGH);         
}

void resetBEDPins() {
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH); // se opreste comanda 
}

void StepForwardDefault(int nr) {
  Serial.println("Miscare inainte cu pasul motorului.");
  digitalWrite(dir, LOW);
  for (x = 1; x < nr; x++) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
  }

}

void ReverseStepDefault(int nr) {
  Serial.println("Miscare inversa cu valoarea pasului");
  digitalWrite(dir, HIGH);
  for (x = 1; x < nr; ++x) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
  }

  Serial.println();
}

void SmallStepMode(int nr) {
  Serial.println("Miscare 1/16 micropasire.");
  digitalWrite(dir, LOW);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (x = 1; x < nr; x++) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
  }

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

  Serial.println();
}

float masurareSenzor(int pinInfrarosu) {
  valoareSenzor = analogRead(pinInfrarosu);
  Serial.println(valoareSenzor);
  float dist = map(valoareSenzor, 10, 400, 10, 80);
  Serial.println(dist);
  delay(400);
  return dist;
}

float masurareSenzorForta(int pinForta) {
  float val = analogRead(pinForta);
  if (val > 0) {
    Serial.print("Nivel de apasare: ");
    Serial.print(val);
    Serial.println();
    delay(100);
    return val;
  }
}
