%Testing for part 5

d = 3;
A = perspective_proj_map(d);
test = [2;3;-4];
A_proj_rect = A * r3_to_hom(test);
A_proj_rect2 = hom_to_r3(A_proj_rect) / A_proj_rect(4,1)

A2 = [test(1,1)/(1 -(test(3,1)/d));test(2,1)/(1 -(test(3,1)/d));0]

%running the above code for any d gives you the same two matrices
%A and A_proj_rect2 regardless of the method used






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