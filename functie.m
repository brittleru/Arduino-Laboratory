function yPRIM=functie(x,y)
% a- alfa b-beta

%notatii
Ia = 2.3; 
Ib = Ia;
Ra = 0.72; Rb = Ra;
ua = Ra * Ia;
ub = Rb * Ib;
L0 = 0.83 * 10^(-3);
Lp = 0.05 * 10^(-3);
pz = 50;
Dr = 0.001;
omega = 3.7699; %omega motor
omega1 = 2.2947; %omega pe rotile 2 si 3
omega2 = 0.5884; %omega pe roata 4
Jredus = 1.2353e-004;
Mrdl = 0.011;

Mredus = (Mrdl * omega2) / omega;
Laa = L0 + Lp * cos(pz * y(3));

%tetas=pi/2 constanta care variaza unghiul electric
Lbb = L0 + Lp * cos(pz * y(3) - pz * pi / 2);
Lab = Lp * sin(pz * y(3));
DLaa = -pz * Lp * sin(pz * y(3));
DLbb = -pz * Lp * sin(pz * y(3) - pz * pi / 2);
DLab = pz * Lp * cos(pz * y(3));

MatDL = [DLaa DLab;DLab DLbb];
MatL = [Laa Lab;Lab Lbb];

Tens = [ua - Ra * y(1); ub - Rb * y(2)];
A = MatDL * [y(1); y(2)]* y(4);
MatDERIV = MatL \ Tens - MatL \ A;

yPRIM(1) = MatDERIV(1);
yPRIM(2) = MatDERIV(2);
yPRIM(3) = y(4);

%Mrdl=Moment redus dispozitiv lucru
Mem = 1 / 2 * (y(1)^2 * DLaa + y(2)^2 * DLbb) + y(1) * y(2) * DLab;
yPRIM(4) = 1 / Jredus *(Mem - Mredus - Dr * y(4));
yPRIM = [yPRIM(1); yPRIM(2); yPRIM(3); yPRIM(4)];