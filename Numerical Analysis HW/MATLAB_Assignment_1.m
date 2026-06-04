%R3 = [2 4;2 6;12 0]
%r4 = r3_to_hom(R3)
%r3 = hom_to_r3(r4)

rect_pts = [1 2 2 1 1;
             2 2 5 5 2;
             3 3 3 3 3];
hom_rect_pts = [r3_to_hom(rect_pts(1:3,1)) r3_to_hom(rect_pts(1:3,2)) r3_to_hom(rect_pts(1:3,3)) r3_to_hom(rect_pts(1:3,4))  r3_to_hom(rect_pts(1:3,5))];

new_rect_pts = Projection_Shape(2,3,-4,rect_pts)

plot3(new_rect_pts(1,:),new_rect_pts(2,:),new_rect_pts(3,:), ...
      rect_pts(1,:),rect_pts(2,:),rect_pts(3,:), ...
      [2 1],[3 2],[-4 3], ...
      [2 2],[3 2],[-4 3], ...
      [2 2],[3 5],[-4 3], ...
      [2 1],[3 5],[-4 3])
axis equal



% rotated_rect_pts = plane_rotation_mat(2,pi) * hom_rect_pts
% 
% rotated_rect_pts = hom_to_r3(rotated_rect_pts)
% 
% hold on
% plot3(rotated_rect_pts(1,:),rotated_rect_pts(2,:),rotated_rect_pts(3,:))
% plot3(rect_pts(1,:),rect_pts(2,:),rect_pts(3,:))
% axis equal

% d = 3;
% A = perspective_proj_map(d);
% test = [2;3;-4];
% A_proj_rect = A * r3_to_hom(test);
% A_proj_rect2 = hom_to_r3(A_proj_rect) / A_proj_rect(4,1)
% 
% A2 = [test(1,1)/(1 -(test(3,1)/d));test(2,1)/(1 -(test(3,1)/d));0]

function r4 = r3_to_hom(X)
    e = size(X);
    r4 = [X;ones(1,e(1,2))];
end

function r3 = hom_to_r3(X)
    e = size(X);
    r3 = eye(3,4) * X;
end

%rotate = plane_rotation_mat(1,pi/3)


function rotate = plane_rotation_mat(iplane,gamma)
   if iplane == 1
       rotate = [cos(gamma) -sin(gamma) 0 0;
                sin(gamma) cos(gamma) 0 0;
                0 0 1 0;
                0 0 0 1]
   end
   if iplane == 2
       rotate = [cos(gamma) 0 -sin(gamma) 0;
                0 1 0 0;
                sin(gamma) 0 cos(gamma) 0;
                0 0 0 1]
   end
   if iplane == 3
       rotate = [1 0 0 0;
                0 cos(gamma) -sin(gamma) 0 ;
                0 sin(gamma) cos(gamma) 0;
                0 0 0 1]
   end
end


function PPM = perspective_proj_map(d)
    PPM = [1 0 0 0;
           0 1 0 0;
           0 0 0 0;
           0 0 -1/d 1];
end

%Below both counts for #6 and #7 of the hw, it just felt
%Easier to do it for any perspective point tbh.
%Projection function does as in name, but only for one variable.
%Projection_Shape does it for an arbitrary n-sided polygon. Altho
%My code is likely bad will probably only work for rectangles

function True_Proj = Projection(d1,d2,d3,V)
    TransV = V - [d1;d2;0]
    Proj_Hom = perspective_proj_map(d3) * r3_to_hom(TransV)
    ProjV = hom_to_r3(Proj_Hom) / Proj_Hom(4,1)
    True_Proj = ProjV + [d1;d2;0]

end


% rect_pts = [1 2 2 1 1;
%             2 2 5 5 2;
%             3 3 3 3 3];


function Shape_Proj = Projection_Shape(d1,d2,d3,A)
    Projected_Points = []
    for n = 1:size(A,2)
        Vn = Projection(d1,d2,d3,A(1:end,n));
        Projected_Points = [Projected_Points Vn];
    end
    Shape_Proj = Projected_Points
end
