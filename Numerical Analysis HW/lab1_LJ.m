
MySecantMethod(0.01,1,0.000001,50,@(x) ((50000+(10000/x))*exp(20*x))-(10000/x)-1000000)

function [result] = MySecantMethod(x1,x2,tol,Nmax,f)
arguments
    x1 double
    x2 double
    tol double
    Nmax double
    f function_handle
end
    xs = [x1; x2];
    ys = [f(x1); f(x2)];
    xn = x2 - (f(x2))*((x2-x1)/(f(x2)-f(x1)));
    i = 2;
    while abs(f(xn)) > tol && i < Nmax
       xn = x2 - (f(x2))*((x2-x1)/(f(x2)-f(x1))); 
       xs = [xs; xn];
       ys = [ys; f(xn)];
       x1 = x2;
       x2 = xn;
       i = i + 1;
    end
    cols = {'x';'y'};
    xn = xs
    yn = ys
    T = table(xn,yn);
    result = T;
end