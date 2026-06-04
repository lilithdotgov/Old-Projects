%Functions for part 1 of hw

%Future Lilith here, WOW my Matlab skills were awful in the past. This
%isn't too egregious, but just wait!

function r4 = r3_to_hom(X)
    e = size(X);
    r4 = [X;ones(1,e(1,2))];
end

function r3 = hom_to_r3(X)
    e = size(X);
    r3 = eye(3,4) * X;
end