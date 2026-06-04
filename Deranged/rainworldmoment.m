pause('on')

ending = 6*pi;
numFrames = 1000;
x = cos(0:ending/numFrames:ending);
y = sin(0:ending/numFrames:ending);
t = 0:1/1000:1;
hold on

plot3(t,y,x,LineWidth=2,Color=[100/255,150/255,200/255])
f = gcf;
f.Position = [0 0 1080 1080];
f.Color = [40/255 5/255 105/255];
% box on
axis off

h = animatedline('Marker','.',MarkerSize=35,Color=[245/255, 235/255, 100/255]);

view(90,0)

v = VideoWriter('RW2.mp4','MPEG-4'); %flag
v.Quality = 100; %flag
open(v); %flag


for i = [1:numFrames] 
    view(POV(i,numFrames));
    %pause(0.001)
    clearpoints(h)
    addpoints(h,t(1,i),y(1,i),x(1,i));
    drawnow
    
     
    frame = getframe(gcf); %flag
    img = frame2im(frame); %flag
    blur = imgaussfilt(img,3); %flag
    fuse = imfuse(img,blur,'blend'); %flag
    finalFrame = im2frame(fuse); %frame

    writeVideo(v, finalFrame); %flag

end


close(v); %flag

clearpoints(h)
hold off

function [result] = POV(t,numFrames) 
    a = 1*numFrames/6;
    b = 2*numFrames/6;
    c = 3*numFrames/6;
    d = 4*numFrames/6;
    e = 5*numFrames/6;
    
    if t < a 
        result = [90, 0];
    elseif t < b
        result = [90 - 45*Ease(t-1-a,numFrames/6),0 + 45*Ease(t-1-a,numFrames/6)];
    elseif t < c
        result = [45, 45];
    elseif t < d
        result = [45 - 45*Ease(t-1-a,numFrames/6),45 - 45*Ease(t-1-a,numFrames/6)];
    elseif t < e
        result = [0,0];
    else
        result = [0 + 90*Ease(t-1-a,numFrames/6),0];
    end
end

function [result] = Ease(t,T)
    result = (1/2)*(sin((pi*t)/T - pi/2) + 1);
end