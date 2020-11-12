# Arduino-Laboratory

## 1'st Laboratory 

In timpul acționării sistemului mecatronic, motorul electric dezvoltă cuplu electromagnetic. Acest cu
plu trebuie să fie egal în orice moment cu momentul rezistent, adică cel creat de sarcina acționată.
De aceea, motorul electric consumă curent de la rețeaua de alimentare. Această variație a curentului
poate fi înregistrată cu senzor de curent. Măsurarea se face pe pinul analogic de la ARDUINO (Fig. 1).

![arduino](https://github.com/brittleru/Arduino-Laboratory/blob/main/lab1-img1.png?raw=true)

## 2'nd Laboratory

### Motor Pas cu Pas Unipolar

#### Caracteristici tehnice

Tensiunea de alimentare: 5 – 12 V current continuu <br>
Frecventa: 100 Hz <br>
Unghiul de pas: comanda pas cu pas 11.250 si 32 de pasi pe rotatie <br>
Comanda micropasire 1 / 2 pas 5.625 de grade. Se executa 64 pasi pe rotatie.<br>
Are reductor cu raport de transmitere 64 : 1 <br>
Turatia la 5V: 15 rotatii pe minut

![Comutare Actionare](https://github.com/brittleru/Arduino-Laboratory/blob/main/lab2-img1.png?raw=true)
![Driver ULN 2003](https://github.com/brittleru/Arduino-Laboratory/blob/main/lab2-img2.png?raw=true)
![Legare Arduino](https://github.com/brittleru/Arduino-Laboratory/blob/main/lab2-img3.png?raw=true)

## 3'rd Laboratory

### Motoare pas cu pas Bipolare

Se foloseste driverul A-4988 pentru motoare bipolare de 2A/faza. Pentru valore de 1.4 pana la 1.7 A/faza
exista racire ativata pe placa, dar pentru valori mai mari trebuie asigurata racirea motorului. Tensiunea
maxima de actionare este de 30V. Pe placa este un regulator pentru 2A/faza. Legarea fazelor motorului se
face conform figurii de mai jos. Sursa de alimentare poate sa aiba 8V la 35V si sa asigure 2A.

![Schema arduino](https://github.com/brittleru/Arduino-Laboratory/blob/main/scheme.png?raw=true)

Se va folosi un senzor de distanta cu infrarosu Sharp GP2Y0A21YK (10cm - 80cm) si un senzor de forta/presiune.


