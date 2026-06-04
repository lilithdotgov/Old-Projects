//Problem 8.8:
#include "stochastics.h"

int p8_8(){ //Random Variable N as described in the problem
	int total = 0; double sum = 0;
	while (sum < 1){
		sum = sum + U(0,1);
		total++;
	}
	return total;
}



int main(){
	srand(initial_seed);
	samples = 1000;
	double mean = E(p8_8,samples);
	srand(initial_seed);
	double variance = Var(p8_8,samples);
	
	printf("%s%f\n","Expected Value of N: ",mean);
	
	printf("%s%f\n","Variance of Estimator: ",variance/samples);
	
	printf("%s%f%s%f\n","95% Confidence Interval for Theta: ",mean-1.96*sqrt(variance/samples),"-",mean+1.96*sqrt(variance/samples));
}

/*
Output:
Expected Value of N: 2.681000
Variance of Estimator: 0.000707
95% Confidence Interval for Theta: 2.628894-2.733106
*/

/*
Discussion:
I imported old code from an earlier assignment, and just threw my pre-made functions at the problem. Not much more to say other than how
useless that variance is, SD is so much more useful as a metric.
*/