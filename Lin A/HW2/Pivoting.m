% failures = 0;
% for i=1:1000
%     A = randi(8,8);
%     [L,U,P] = luwpiv(A);
%     %[L2,U2,P2] = lu(A);
%     if max(max(L*U-P*A)) > 0.000000000001
%        failures = failures + 1;
%     end    
% end
% failures
A = [3 -2 -3; 9 -2 -12; -12 12 5];

[L,U,P] = luwpiv(A)

function [L,U,P] = luwpiv(A)
    [m,n] = size(A);
    assert(m==n);
    P = eye(n);
    L = eye(n);
    U = A;
    for i = 1:(n-1)
        mid = max(abs(U(i:end,i)));
        elem = find(abs(U(i:end,i))==mid);
        elem = elem(1)+i-1;

        temprow = U(i,:);
        U(i,:) = U(elem,:);
        U(elem,:) = temprow;

        temprow = L(i,1:i-1);
        L(i,1:i-1) = L(elem,1:i-1);
        L(elem,1:i-1) = temprow;

        temprow = P(i,:);
        P(i,:) = P(elem,:);
        P(elem,:) = temprow;
        for j = i+1:n
                L(j,i) = U(j,i)/U(i,i);
                U(j,i:n) = U(j,i:n)-L(j,i)*U(i,i:n);
        end
    end
    U = triu(U);
    L = tril(L);
end