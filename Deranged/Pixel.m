A = @(a,b,c) ...
    (1/(a+b+c)).*[(a*4/12)+(b*2/12) 0 (b*2/12)+(c*4/12)
     0 (c*4/12)+(b*2/12) (b*2/12)+(a*4/12)
     (a*2/12)+(b*1/12) (c*2/12)+(b*1/12) (a*2/12)+(b*2/12)+(c*2/12)];
a = 14;
b = 20;
c = 8;
x = [a; b; c];

t = 10;

Data = Evolution(A,x,t)

function [result] = Evolution(A,x,t)
    X = x;
    for i=[1:1:t]
        X = [X A(X(1,i),X(2,i),X(3,i))*X(1:3,i)];
    end
    result = X;
end