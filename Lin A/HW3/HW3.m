HousingData = readtable("HousingData.csv");
HousingData = table(HousingData{:,1},HousingData{:,2},HousingData{:,3},HousingData{:,4},HousingData{:,5},HousingData{:,6},...
              'VariableNames',["ZIP code","# of bedrooms","# of bathrooms","area in ft2","Condo? (Yes/No = 1/0)","price in USD"]);

%MATLAB Question 1

% tile = tiledlayout(2,2);
% fig = gcf;
% fig.Color = [3, 12, 54]./255;
% 
% TL = nexttile;
% X = HousingData{:,"# of bedrooms"};
% Y = HousingData{:,"price in USD"}./10000;
% C = HousingData{:,"# of bathrooms"};
% scatter(X,Y,[],C,"filled")
% a=colorbar;
% a.Label.String = "# of bathrooms";
% a.Color = [255, 232, 168]./255;
% C=parula(5);
% colormap(TL,C)
% a.Ticks = linspace(1,5,6)+0.45;
% a.TickLabels = {'1','2','3','4','5'};
% xlabel(TL,"# of bedrooms")
% ylabel(TL,"price in 10,000 USD")
% TL.Color = [3, 12, 54]./255;
% TL.XColor = [255, 232, 168]./255;
% TL.YColor = [255, 232, 168]./255;
% grid on
% 
% TR = nexttile;
% X = HousingData{:,"area in ft2"};
% Y = HousingData{:,"# of bedrooms"};
% C = HousingData{:,"# of bathrooms"};
% scatter(X,Y,[],C,"filled")
% a=colorbar;
% a.Label.String = "# of bathrooms";
% a.Color = [255, 232, 168]./255;
% a.Ticks = linspace(1,5,6)+0.45;
% a.TickLabels = {'1','2','3','4','5'};
% C=parula(5);
% colormap(TR,C)
% xlabel(TR,"area in ft²")
% ylabel(TR,"# of bedrooms")
% TR.Color = [3, 12, 54]./255;
% TR.XColor = [255, 232, 168]./255;
% TR.YColor = [255, 232, 168]./255;
% grid on
% 
% BT = nexttile([1 2]);
% X = HousingData{:,"area in ft2"};
% Y = HousingData{:,"price in USD"}./10000;
% S = 5*(HousingData{:,"# of bedrooms"}.^2);
% C = HousingData{:,"ZIP code"};
% scatter(X,Y,S,C)
% a=colorbar;
% a.Label.String = "ZIP code";
% a.Color = [255, 232, 168]./255;
% a.Ticks = linspace(1,4,5)+0.45;
% a.TickLabels = {'1','2','3','4'};
% C=parula(4);
% colormap(BT,C)
% xlabel(BT,{"area in ft²","circle area ∝ # of bedrooms²"})
% ylabel(BT,"price in 10,000 USD")
% BT.Color = [3, 12, 54]./255;
% BT.XColor = [255, 232, 168]./255;
% BT.YColor = [255, 232, 168]./255;
% grid on

%Pen and Paper Question 1

%Looking at the top-left figure, there seems to be a positive correlation
%between both the # of bedrooms and # of bathrooms and the price of the 
%house. Albeit, it's more clear to see for the # of bathrooms. Looking at
%the top-right figure there iis a very obvious positive relationship
%between both # of bathrooms and # of bathrooms when it comes to house
%area. The increase in # of bedrooms seems somewhat logarithmic just from
%pattern matching in my brain. Finally, the bottom plot  shows a clear
%positive linear relationship between price and area, and maybe a similar
%relationship for price and # of bedrooms, although it's hard to tell by
%visuals alone. Interestingly, there are almost no houses in zip code 1
%that are larger than 2500 ft². This could indicate the area as being a
%more urban one and so buildings may be maximizing their usage of area by
%building taller, apartment-style housing. 

%Matlab Question 2

%Larger model
A = HousingData{:,2:5};
b = HousingData{:,6};

c1 = A\b;

c2 = (A'*A)\(A'*b);

[Q,R] = qr(A,0);
c3 = inv(R)*transpose(Q)*b;

Residual1 = norm(A*c1-b)./norm(b);
Residual2 = norm(A*c2-b)./norm(b);
Residual3 = norm(A*c3-b)./norm(b);

t1 = table(c1,c2,c2,VariableNames={'c1','c2','c3'})
t2 = table(Residual1,Residual2,Residual3,VariableNames={'Residual c1','Residual c2','Residual c3'})

%Smaller model
A = HousingData{:,[2 4]};
c = A\b
Residual = norm(A*c-b)./norm(b)

R = [];
for i=[-100000:1:100000]
    c = [i; 142.6937-i*0.0019];
    Residual = norm(A*c-b)./norm(b);
    R = [R; Residual];
end

plot(-100000:1:100000,R);

%Pen and Paper Question 2

%Region ID doesn't really have any numeric meaning (ok, technically it 
%*does* since we don't assign zip codes and the like randomly like in 
%Ireland) and so the metric you'd be fitting the data to wouldn't be 
%useful for any analysis. 
%
%Unsurprisingly, the residuals of the larger and
%smaller model are mostly the same since it seems all of the data sets
%follow the same similar trend when compared to house area. 
% 
%The coefficients seem almost wrong, since one is negative, but you must
%recall that this isn't a comparison of one of the variables vs. prices,
%this model takes into account of both. If we were looking at individual
%variables then the coefficients ARE positive (just # of bedroom vs. price
%has a coefficient of 7.0149e+04, and area vs. price is 142.6937), which 
%makes sense to use. It's much harder to wrap your head around an 
%n-dimensional model and what the coefficients mean, which is why it's 
%likely beter to look at different things like—as an idea—the singular 
%values of A. So, it's not too surprising once you think about it for a
%second.
%
%Observing that the house area and # of bedrooms are correlated makes it
%more clear what is occuring. If price increased linearly as house area
%increased, but # of bedrooms also increased linearly (or logarithmic as
%stated before) with house area, we'd end up with just a single variable 
%relationship. 
%
%Say that p = c1*b + c2*a represents price vs. # of bedrooms and area. Say
%then, that we also have the relationship b = c3*a which represents # of
%bedrooms vs. area. Therefore, p = c1*c3*a+c2*a = a*(c1*c3+c2). We can just
%find c3, it's 0.0019. Now let c4 = (c1*c3+c2), and we can just find a
%relationship between price and area, p = c4*a. We obtain c4 = 142.6937
%(which is the same value as before!). So we obtain 142.6937 = c1*0.0019
%+c2. This gives us a line of valid values which solve for this equation,
%and if we plug in the obtained values for c1 and c2 it is indeed a
%solution to this equation. There is some restriction on what values c1 or 
%c2 can be, both can either be negative or positive, but you can't have 
%both be negative at the same time. This makes sense!
%
%As an aside: When comparing values for c1 and c2 vs. residual, it's clear
%that this can't be a linear relationship otherwise there would not be a
%global minimum. However, I can't seem to derive what the big-O of the 
%function would be. I keep getting a linear relationship between residual
%and c1. Odd... I'll maybe talk to you in office hours about this if I have
%time!