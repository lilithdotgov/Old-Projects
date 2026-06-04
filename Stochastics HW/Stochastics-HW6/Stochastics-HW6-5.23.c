//Problem 5.23:
#include "stochastics.h"

double p5_23_rejection(){
	double cinv = 1.0/1.13542; //We take the reciprocal of c here
	double l = 373.0/20.0;
	double rv1 = U(0,1);
	double rv2 = 0.8 + (-1.0/l)*log(U(exp(-l/5.0),1));
	double q = (62500.0/21.0)*(1 - exp(-0.2*l))/l; //Added constant just to make next line less awful to read
	double attempt = cinv*q*rv2*pow(1 - rv2,3)*exp(l*(rv2 - 0.8));
	while (rv1 > attempt){
		rv1 = U(0,1);
		rv2 = 0.8 + (-1.0/l)*log(U(exp(-l/5.0),1));
		attempt = cinv*q*rv2*pow(1 - rv2,3)*exp(l*(rv2 - 0.8));
	}
	return rv2;
}		
	
int main(){
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.23 Rejection Method:\t ", E(p5_23_rejection, samples)); //Sanity check
}

/*
Output:
Mean of Problem 5.23 Rejection Method:   0.841257
*/

/*
Discussion:
So... this was quite a test of my persistence. I realized the function looked a lot like an exponential, but exponentials need to go to infinity
in order to be a real pdf with area = 1, so I decided to just scale it by a constant dependent on lambda. This was 1 - e^(-0.2*l) which is not
so bad! Then I found the derivative with respects to x, and found that the roots must be l = (1 - 4*x)/((x - 1)*x) which is also nice!
I expected to then derivate with respects to lambda, get a nice expression, solve a simple equation, and minimize our c! Instead, I got an
abomination that even Wolfram Alpha could not solve for...

I kept trying to desperately find the optimal lambda but it's not worth the effort, I'm just setting lambda to 18.65 or 373/20 because the number
gave a pretty good c around 1.13542, which while not optimal, is pretty good! 	
*/