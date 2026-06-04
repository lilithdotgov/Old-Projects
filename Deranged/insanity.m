% 0 : 9
% 1 : 13, 18, 21
% 2 : 7, 19
% 3 : 26
% 4 : 19, 20
% 5 : 8
% 6 : 18, 22
% 7 : 2, 11, 26
% 8 : 5, 12, 18
% 9 : 0
%10 : 25, 27
%11 : 7, 14
%12 : 8, 16, 22, 27
%13 : 1, 18
%14 : 11, 23
%15 : 17
%16 : 12, 25
%17 : 15
%18 : 1, 6, 8, 13
%19 : 2, 4, 24
%20 : 4
%21 : 1
%22 : 6, 12
%23 : 14, 25
%24 : 19, 25
%25 : 10, 16, 23, 24
%26 : 3, 7
%27 : 10, 12

RW = zeros(28,28);
RW(1,10) = 1;
RW(2,[14 19 22]) = 1;
RW(3,[8 20]) = 1;
RW(4,27) = 1;
RW(5,[20 21]) = 1;
RW(6,9) = 1;
RW(7,[19 23]) = 1;
RW(8,[3 12 27]) = 1;
RW(9,[6 13 19]) = 1;
RW(10,1) = 1;
RW(11,[26 28]) = 1;
RW(12,[8 15]) = 1;
RW(13,[9 17 23 28]) = 1;
RW(14,[2 19]) = 1;
RW(15,[12 24]) = 1;
RW(16,18) = 1;
RW(17,[13 26]) = 1;
RW(18,16) = 1;
RW(19,[2 7 9 14]) = 1;
RW(20,[3 5 25]) = 1;
RW(21,5) = 1;
RW(22,2) = 1;
RW(23,[7 13]) = 1;
RW(24,[15 26]) = 1;
RW(25,[20 26]) = 1;
RW(26,[11 17 24 25]) = 1;
RW(27,[4 8]) = 1;
RW(28,[11 13]) = 1;

hold on
M = size(RW,1);
plot(polyshape([0,0;0,M;M,M;M,0;0,0]), FaceColor = [1 1 1], LineStyle = "none", FaceAlpha = 1)

Perm = eye(M);
Perm = Perm(randperm(M),:);
RW = Perm * RW * Perm';

Poly = CreatePoly(RW);
Map(Poly)

f = gcf;
f.Position = [270 0 900 750];
f.Color = [0.9 0.9 0.9];
axis off
hold off

function [result] = CreatePoly(A)
    M = size(A,1);
    P = {};
    i = 1;
    for x = 1:1:M
        for y = 1:1:M
            if A(x,y) == 1
                P{i} = polyshape([x-1, M-y+1; x, M-y+1; x, M-y; x-1, M-y; x-1, M-y+1]);
                i = i + 1;
            end
        end
    end
    result = P;
end

function Map(S)
    for i = 1:1:size(S,2)
        plot(S{i}, FaceColor = [0 0 0], LineStyle = "none", FaceAlpha = 1)
    end
end