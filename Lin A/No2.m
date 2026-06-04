%Function for part 2

%This just looks visually bad, I should've aligned the rows.

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