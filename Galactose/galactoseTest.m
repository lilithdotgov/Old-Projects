%So far we have learnt that if all of the variables are > 1, it NEVER
%converges. Which is neat.
%So, obviously if the magnitude of all parameters is 6 or less, we are fine
%And when it's 7 or more it's not fine. But that interval between 6 and 7
%seems to mostly be divergence, but some DO converge, and all of these have
%at least 1 eval with magnitude less than 1.

%Although, analyzing this stuff is kinda dumb. We need to focus on
%realistic bounds between 0 and 1, and look at continuous input 

%Ok, it seems that periodicity is baked in... which actually makes some
%sense. Oop.

%FUCCCCKKK. We need to analyze the evals of A'*A, cuz of singular value
%decomposition, since our matrix is NOT invertible bc of the 0 eval, and
%thus not diagnalizable in the same way.

A = 6;
B = 7;

Diverges = 0;
Periodic = 0;
for n = [0:3000]
    
    % a = A + (B-A)*rand;
    % b = A + (B-A)*rand;
    % c = A + (B-A)*rand;
    % d = A + (B-A)*rand;
    % e = A + (B-A)*rand;
    % f = A + (B-A)*rand;

    % while true
    %     a = (B/6)*rand;
    %     b = (B/6)*rand;
    %     c = (B/6)*rand;
    %     d = (B/6)*rand;
    %     e = (B/6)*rand;
    %     f = (B/6)*rand;
    % 
    %     if a+b+c+d+e+f > A && a+b+c+d+e+f < B
    %         break
    %     end
    % end

    a = rand;
    b = rand;
    c = rand;
    d = rand;
    e = rand;
    f = rand;

    %These affect constant input to the system, set to 0 to ignore
    G1 = rand;
    G2 = rand;
    
    t = table(a,b,c,d,e,f);
    
    U = [0 0 0 0 e -f 0 0; 
        -a 0 0 0 0 0 1 0; 
        0 -b 0 0 0 0 b 0; %It should be a constant value such that -b makes it 0. Therefore I made it b. Seems right?
        0 0 0 0 0 d 0 0; 
        0 0 0 0 1-e-c 0 G1 0; 
        0 0 c 0 0 1-f-d G2 0;
        0 0 0 0 0 0 1 0;
        0 0 0 1 0 0 0 1];
    
    svd(U)

    lambda = eig(U'*U)

    % if max(abs(real(lambda))) > 1
    %    Diverges = Diverges + 1;
    %    [G1,G2]
    % end
    % 
    % if max(abs(imag(lambda))) > 0
    %     Periodic = Periodic + 1;
    %     [G1,G2]
    % end
end
% Diverges
% Periodic