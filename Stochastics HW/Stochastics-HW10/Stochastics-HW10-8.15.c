//Problem 8.15:
#include "stochastics.h"

int Data[] = {5, 4, 9, 6, 21, 17, 11, 20, 7, 10, 21, 15, 13, 16, 8};

int Fe(){ //Random variable of interest
	return Data[(int)(15*U(0,1))];
}

double Fe_Var(){ //Gives variance of Fe
	double sum = 0;
	double mean = 0;
	
	for(int i = 0; i < 15; i++){ //Find our distribution mean
		mean = mean + Data[i];
	}
	mean = mean/15.0;
	
	for(int i = 0; i < 15; i++){ //Find our distribution variance
		sum = sum + pow(Data[i] - mean, 2);
	}
	return sum/(15.0-1.0);
}

double s2; //Mutable Global variables are evil, but it's easier to write it like this

double p8_15(){ //A single realization of estimate
	int realization[15];
	for(int i = 0; i < 15; i++){
		realization[i] = Fe();
	}
	
	double mean = 0;
	for(int i = 0; i < 15; i++){ //Find our distribution mean
		mean = mean + realization[i];
	}
	mean = mean/15.0;
	
	double sum = 0;
	for(int i = 0; i < 15; i++){ //Find our distribution variance
		sum = sum + pow(realization[i] - mean, 2);
	}
	return pow((sum/(15.0-1.0)) - s2, 2);
	
}



int main(){
	srand(initial_seed);
	samples = 1000000;
	s2 = Fe_Var();
	printf("%s%f\n","Bootstrap Estimate of Var(S^2): ",E(p8_15,samples));
}

/*
Output:
Bootstrap Estimate of Var(S^2): 63.649287
*/

/*
Discussion:
Just reused code from prior assignments, nothing new to add other than making the random variable output 4 instead of 1 like in the book.
This way we get an expected value of exactly pi, rather than pi/4.
*/