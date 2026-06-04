%Function for part 4

%It's fine

function PPM = perspective_proj_map(d)
    PPM = [1 0 0 0;
           0 1 0 0;
           0 0 0 0;
           0 0 -1/d 1];
end