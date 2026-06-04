//Problem 5.20:
#include "stochastics.h"

double p5_20_rejection(){
	double cinv = sqrt(exp(1))/2.0; //We take the reciprocal of c here
	double l = (-1.0 + sqrt(5))/2.0;
	double rv1 = U(0,1);
	double rv2 = (-1.0/l)*log(U(0,1));
	double attempt = cinv*(1.0/(2.0*l))*(1+rv2)*exp((-1+l)*rv2);
	while (rv1 > attempt){
		rv1 = U(0,1);
		rv2 = (-1.0/l)*log(U(0,1));
		attempt = cinv*(1.0/(2.0*l))*(1+rv2)*exp((-1+l)*rv2);
	}
	return rv2;
}	
	
int main(){
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.20 Rejection Method:\t ", E(p5_20_rejection, samples)); //Sanity check
}

/*
Output:
Mean of Problem 5.20 Rejection Method:   1.500265
*/

/*
Discussion:
Used le^(-l*x) as my distribution, differentiating with respects to l and x gives two equations with positive roots at x = 1/l and x = l/(1 - l). 
Therefore the optimal lambda is the solution of 1/l = 1/(l - 1), which ends up being the polynomial l^2 + l - 1 = 0. Whose solution is the 
infamous golden ratio! Or well, it's (-1 + sqrt(5))/2 which is the negative reciprocal of the golden ratio! Let p = golden ratio, then this 
optimizes c to be ((1/2) + p)*e^(-1/p) = 1.1416 which is pretty good! 

*/