%It honestly felt easier to just do number 7 instead of 6,
%And since the code for number 7 also works for number 6
%I just did number 7. Tested it via some awful code, but it works

%Everything below here is future Lilith:
%Ok... Now to find my prior error. 
%I think I found it? Err, maybe it was never an error in the first place?
%Maybe you just wanted to show how objects closer should be bigger, but my
%example has an object that is farther from z = 0 and so the projection is
%smaller?
%I genuinely can't see any other possible avenue for error, it looks fine?
%Oh well, I'm submitting this and I'll find out soon enough what the issue
%was I suppose.

rect_pts = [1 2 2 1 1;
            2 2 5 5 2;
            3 3 3 3 3];
hom_rect_pts = [r3_to_hom(rect_pts(1:3,1)) r3_to_hom(rect_pts(1:3,2)) r3_to_hom(rect_pts(1:3,3)) r3_to_hom(rect_pts(1:3,4))  r3_to_hom(rect_pts(1:3,5))];

new_rect_pts = Projection_Shape(2,3,-4,rect_pts);

plot3(new_rect_pts(1,:),new_rect_pts(2,:),new_rect_pts(3,:), ...
      rect_pts(1,:),rect_pts(2,:),rect_pts(3,:), ...
      [2 1],[3 2],[-4 3], ...
      [2 2],[3 2],[-4 3], ...
      [2 2],[3 5],[-4 3], ...
      [2 1],[3 5],[-4 3])
axis equal

%Functions below



function PPM = perspective_proj_map(d)
    PPM = [1 0 0 0;
           0 1 0 0;
           0 0 0 0;
           0 0 -1/d 1];
end

function r4 = r3_to_hom(X)
    e = size(X);
    r4 = [X;ones(1,e(1,2))];
end

function r3 = hom_to_r3(X)
    e = size(X);
    r3 = eye(3,4) * X;
end

function True_Proj = Projection(d1,d2,d3,V)
    TransV = V - [d1;d2;0];
    Proj_Hom = perspective_proj_map(d3) * r3_to_hom(TransV);
    ProjV = hom_to_r3(Proj_Hom) / Proj_Hom(4,1);
    True_Proj = ProjV + [d1;d2;0];

end

function Shape_Proj = Projection_Shape(d1,d2,d3,A)
    Projected_Points = []
    for n = 1:size(A,2)
        Vn = Projection(d1,d2,d3,A(1:end,n));
        Projected_Points = [Projected_Points Vn];
    end
    Shape_Proj = Projected_Points;
end