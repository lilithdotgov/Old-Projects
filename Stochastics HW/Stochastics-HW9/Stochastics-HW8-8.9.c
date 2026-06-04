//Problem 8.9:
#include "stochastics.h"

int p8_9(){ //Random Variable N as described in the problem
	int total = 0; double prev_U = 0; double new_U = 0;
	
	prev_U = U(0,1);
	total++;
	new_U = U(0,1);
	total++;
	
	while (new_U > prev_U){
		prev_U = new_U;
		new_U = U(0,1);
		total++;
	}
	return total;
}



int main(){
	srand(initial_seed);
	samples = 1000;
	double mean = E(p8_9,samples);
	srand(initial_seed);
	double variance = Var(p8_9,samples);
	
	printf("%s%f\n","Expected Value of N: ",mean);
	
	printf("%s%f\n","Variance of Estimator: ",variance/samples);

	printf("%s%f%s%f\n","95% Confidence Interval for Theta: ",mean-1.96*sqrt(variance/samples),"-",mean+1.96*sqrt(variance/samples));
}

/*
Output:
Expected Value of N: 2.708000
Variance of Estimator: 0.000696
95% Confidence Interval for Theta: 2.656288-2.759712
*/

/*
Discussion:
About the same result as prior, not much to say.
*/