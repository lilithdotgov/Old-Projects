//Problem 5.17:
#include "stochastics.h"

double p5_17_composition(){ //Method 1
	double rv = U(0,1);
	if (rv < 0.5){
		return pow(U(0,1),0.25);
	}
	else if (rv < 0.75){
		return pow(U(0,1),0.2);
	}
	else{
		return U(0,1);
	}
}

double p5_17_rejection(){ //Method 2
	double cinv = 1.0/3.5;
	double rv1 = U(0,1);
	double rv2 = U(0,1);
	double attempt = cinv*(0.25 + 2.0*pow(rv2,3) + 1.25*pow(rv2,4));
	while (rv1 > attempt){
		rv1 = U(0,1);
		rv2 = U(0,1);
		attempt = cinv	*(0.25 + 2.0*pow(rv2,3) + 1.25*pow(rv2,4));
	}
	return rv2;
}

int main(){
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.17 Composition Method: ", E(p5_17_composition, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.17 Rejection Method:\t ", E(p5_17_rejection, samples)); //Sanity check

}

/*
Output:
Mean of Problem 5.17 Composition Method: 0.733296

Mean of Problem 5.17 Rejection Method:   0.733614
*/

/*
Discussion:
The first method is a simple composition by using the distributions x, x^4, and x^5. The second method is a rejection using g(X) = U(0,1).
This *works* but it quite bad as c = 3.5, but better matching functions like x^5 led to c -> inf due to 1/x terms. I couldn't think of a 
better distribution to use for this, but surely it must exist? 
*/