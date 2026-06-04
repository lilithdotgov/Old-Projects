% a = 1/2; %Gal3 binding 
% b = 1/3; %Gal80 binding
% c = 1/3; %EnergyProduction from Gal4/Galactose
% d = 3/5; %EnergyProduction from Glucose
% e = 1/5; %Galactose
% f = 1/5; %Glucose

%An insane and bad idea is rather than using lambda analysis, we do some
%nueral network nonsense to find the perfect variable parameters.
%We can test correctness via the results of the paper

% S0 = [Gal3; Gal80; Gal4; EnergyProduction; Galactose; Glucose; AffineConstant; 0];
% %U = [1 0 0 -a; -b 1 0 0; 0 -c 1 0; 0 0 d e];
% % U = [1-a 0 0 0 e -f; 
% %     -a 1-b 0 0 0 0; 
% %     0 -b 1-c 0 0 0; 
% %     0 0 c 1 0 d; 
% %     0 0 0 0 1-e-c 0; 
% %     0 0 0 0 0 1-f-d];
% 
% U = [0 0 0 0 e -f 0 0; 
%     -a 0 0 0 0 0 1 0; 
%     0 -b 0 0 0 0 b 0; %It should be a constant value such that -b makes it 0. Therefore I made it b. Seems right?
%     0 0 c 0 0 d 0 0; 
%     0 0 0 0 1-e-c 0 0 0; 
%     0 0 0 0 0 1-f-d 0 0;
%     0 0 0 0 0 0 1 0;
%     0 0 0 1 0 0 0 1];

a = 1/2; %Gal3 binding 
b = 1/3; %Gal80 binding
c = 1/3; %Gal4 turning Galactose to Glucose
d = 3/5; %EnergyProduction from Glucose
e = 1/5; %Galactose
f = 1/5; %Glucose

Gal3 = 0; %Should be 0 if from equillibrium
Gal80 = 1; %This should be equal to AffineConstant
Gal4 = 0; %Should be 0 if from equillibrium
EnergyProduction = 0;
Galactose = 5;
Glucose = 2;
AffineConstant = 1; %Just some bs to make values reset each time

%These affect constant input to the system, set to 0 to ignore
G1 = 0.5;
G2 = 0.1;

t = table(a,b,c,d,e,f);


S0 = [Gal3; Gal80; Gal4; EnergyProduction; Galactose; Glucose; AffineConstant; 0];


U = [0 0 0 0 e -f 0 0; 
    -a 0 0 0 0 0 1 0; 
    0 -b 0 0 0 0 b 0; %It should be a constant value such that -b makes it 0. Therefore I made it b. Seems right?
    0 0 0 0 0 d 0 0; 
    0 0 0 0 1-e-c 0 G1 0; 
    0 0 c 0 0 1-f-d G2 0;
    0 0 0 0 0 0 1 0;
    0 0 0 1 0 0 0 1];



Sn = S0;
Points = [S0];
N = 70;

for i=[1:N]
    %Sn = pos(U*Sn); %using pos is a hacccckkkkkk
    Sn = U*Sn;
    Points = [Points Sn];
end

close all

f1 = figure
hold on
movegui(f1,"east")
plot(0:N,Points(1,1:end),DisplayName="Gal3")
plot(0:N,Points(2,1:end),DisplayName="Gal80")
plot(0:N,Points(3,1:end),DisplayName="Gal4")
plot(0:N,Points(4,1:end),DisplayName="EnergyProduction")

plot(0:N,Points(8,1:end),DisplayName="Total Product")



yscale_symlog;
legend(gca,"show"); 
hold off

f2 = figure
hold on
movegui(f2,"west")
plot(0:N,Points(1,1:end),DisplayName="Gal3")
plot(0:N,Points(2,1:end),DisplayName="Gal80")
plot(0:N,Points(3,1:end),DisplayName="Gal4")
plot(0:N,Points(4,1:end),DisplayName="EnergyProduction")

plot(0:N,Points(8,1:end),DisplayName="Total Product")



%yscale_symlog;
legend(gca,"show"); 
hold off


Points;

t;

lambda = eig(U);

deter = det(U);

function [result] = pos(x)
    result = (abs(x)+x)/2;
end
