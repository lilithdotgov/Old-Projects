//Problem 8.13:
/*
Part A Discussion:

*/

//Part B:
#include "stochastics.h"

int Fe[] = {56, 101, 78, 67, 93, 87, 64, 72, 80, 69};


int p8_13(){ //Generates one realization of Fe and its error, then returns 1 if inside the range
	double mean_Fe = 76.7; double a = -5; double b = 5;
	int size_of_Fe = 10;
	
	int realization[size_of_Fe];
	for(int i = 0; i < size_of_Fe; i++){
		realization[i] = Fe[(int)U(0,size_of_Fe)];
	}
	
	double mean = 0;
	for(int i = 0; i < size_of_Fe; i++){ //Find our distribution mean
		mean = mean + realization[i];
	}
	mean = mean/size_of_Fe;
	
	if (((mean - mean_Fe) > a) && ((mean - mean_Fe) < b)){
		return 1;
	}
	else{
		return 0;
	}
}



int main(){
	srand(initial_seed);
	samples = 10000;
	printf("%s%f\n","Bootstrap Estimate of p: ",E(p8_13,samples));
}

/*
Output:
Bootstrap Estimate of p: 0.767300
*/

/*
Discussion:
Originally was going to compute all 10^10 values of gamma since the book doesn't say to simulate p, it just says to estimate p which
this would be an estimate of p! Problem 15 uses the explicit language of "estimate (by simulating)" which implies you don't use simulation
for this one!

However, a 32-bit int is not large enough to store 10^10, and so I don't think my program would terminate for a good few hours even written
optimally. 
*/