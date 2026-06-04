func = @(x,y) y.^2 - 10.*y;
y0 = 5;
for i = [0.1,0.01]
    t0 = 0;
    h = i;
    tn = t0 + 2*h;
    
    y1 = MyRK4(func,y0,t0,tn,h);
    y2 = y1(3,1);
    y1 = y1(2,1);
    
    t0 = tn;
    tn = 5;
    
    points = ABMethod3(func,y0,y1,y2,t0,tn,h);
    
    hold on
    x = transpose(0:h:tn);
    plot(x,points(1:length(x),1),DisplayName="h="+string(i))
    
    
end
%yscale_symlog;
legend
hold off

function [result] = ABMethod3(f,y0,y1,y2,t0,tn,h)
    yn = [y0; y1; y2];
    i = t0;
    while i < tn
        v1 = f(i,yn(end,1));
        v2 = f(i-h,yn(end-1,1));
        v3 = f(i-2*h,yn(end-2,1));
        yn = [yn; yn(end,1) + h*((23/12)*v1 - (16/12)*v2 + (5/12)*v3)];
        i = i + h;
    end  
    result = yn;
end


function [result] = MyRK4(f,y0,t0,tn,h)
    yn = [y0];
    i = t0;
    while i < tn
        v1 = f(i,yn(end,1));
        v2 = f(i+h/2,yn(end,1)+(h/2).*v1);
        v3 = f(i+h/2,yn(end,1)+(h/2).*v2);
        v4 =f(i+h,yn(end,1)+h.*v3);
        yn = [yn; yn(end,1) + (h/6).*(v1+2.*v2+2.*v3+v4)];
        i = i + h;
    end
    result = yn;
end