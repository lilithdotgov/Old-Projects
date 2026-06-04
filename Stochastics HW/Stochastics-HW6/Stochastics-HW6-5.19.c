//Problem 5.19:
#include "stochastics.h"

double p5_19_inversion(){
	return -0.5 + pow(0.25 + U(0,2),0.5);
}

double p5_19_composition(){
	double rv = U(0,1);
	if (rv < 0.5){
		return U(0,1);
	}
	else{
		return pow(U(0,1),0.5);
	}
}

double p5_19_rejection(){
	double cinv = 1.0/1.5;
	double rv1 = U(0,1);
	double rv2 = U(0,1);
	double attempt = cinv*(rv2 + 0.5);
	while (rv1 > attempt){
		rv1 = U(0,1);
		rv2 = U(0,1);
		attempt = cinv*(rv2 + 0.5);
	}
	return rv2;
}	
	
int main(){
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.19 Inverseion Method:\t ", E(p5_19_inversion, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.19 Rejection Method:\t ", E(p5_19_rejection, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.19 Composition Method: ", E(p5_19_composition, samples)); //Sanity check
}

/*
Output:
Mean of Problem 5.19 Inverseion Method:  0.582981

Mean of Problem 5.19 Rejection Method:   0.583644

Mean of Problem 5.19 Composition Method: 0.583389
*/

/*
Discussion:
I think the inversion method is likely best, it has 1 U per X, no comparisons, and is equally computationally intensive as composition. 
The computational intensity is the only upside that rejection has as it's just an addition and multiplication, which means its really
just a multiplication since addition is free with a multiplication down at the CPU layer. Perhaps, this would make it come in second?

But wait! Why huss and fuss about this when we can just time it? Run without optimized gcc settings I got the following average speeds:

Inversion:	 35us 
Rejection:	 42us 
Composition: 39us

Looks like my intuition was wrong, the gain in computational speed was nowhere enough to compensate the 2 U's and 1.5 average failures
with the rejection method. But inversion is number 1 as expected!
*/