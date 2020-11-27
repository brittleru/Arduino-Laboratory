[t1,y1] = ode23('functie', [0 0.05], [0 0 0 0]);
%0.031 timp 1 pas
%grafice
figure(1);
plot(t1, y1(:,1), 'r');
grid;
figure(2);
plot(t1, y1(:,3), 'b');
grid;
figure(3);
plot(t1, y1(:,4),'g');
grid;