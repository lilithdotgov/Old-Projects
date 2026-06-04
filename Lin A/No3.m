%Testing for part 3. This would be easier as a function
%Alas, I am lazy and so I do more work as a consequence

%DEAR MOTHER OF GOD. Why did I do this???
%I'm so sorry you're going to have to read this a second time, I swear I'm
%more competant at Matlab now.

rect_pts = [1 2 2 1 1;
            2 2 5 5 2;
            3 3 3 3 3];
plane1 = plane_rotation_mat(1,pi/4);
plane2 = plane_rotation_mat(2,pi/4);
plane3 = plane_rotation_mat(3,pi/4);
hom_rect_pts = r3_to_hom(rect_pts);
plane1_rec = plane1 * hom_rect_pts;
plane2_rec = plane2 * hom_rect_pts;
plane3_rec = plane3 * hom_rect_pts;
final_rec1 = hom_to_r3(plane1_rec);
final_rec2 = hom_to_r3(plane2_rec);
final_rec3 = hom_to_r3(plane3_rec);

plot3(rect_pts(1,:),rect_pts(2,:),rect_pts(3,:), ...
      final_rec1(1,:),final_rec1(2,:),final_rec1(3,:), ...
      final_rec2(1,:),final_rec2(2,:),final_rec2(3,:), ...
      final_rec3(1,:),final_rec3(2,:),final_rec3(3,:))

axis equal

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

function r4 = r3_to_hom(X)
    e = size(X);
    r4 = [X;ones(1,e(1,2))];
end

function r3 = hom_to_r3(X)
    e = size(X);
    r3 = eye(3,4) * X;
end

