//Problem 8.6:
#include "stochastics.h"

/*
Part a discussion:
Since we know the distribution's actual SD, which is 1, then 1/sqrt(n) < 1/100. Which implies we
need at least 100^2 = 10000 samples to reduce our variability from the true mean to a SD of 1/100.  
*/

struct s_triplet{ //Used to package output data
	int n;
	double mean;
	double s2;
};

struct s_triplet p8_6(){ 
	double s2 = 0; double mean = 0; double d = 0.01; double x_n; //s2 is the sample variance 
	int n = 0;
	
	//First need to handle the n = 1 case, which requires setting s2 = 0
	x_n = exp(pow(U(0,1),2));
	s2 = 0;
	mean = x_n;
	n++;

	
	for(int i = 0; i < 99; i++){ //Generate rest of first 100 terms
		x_n = exp(pow(U(0,1),2));
		s2 = ((n-1.0)/n)*s2 + (pow(x_n - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + x_n)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;
	}
	
	for(;;){
		if (sqrt(s2/n) < d){
			struct s_triplet answer;
			answer.n = n;
			answer.mean = mean;
			answer.s2 = s2;
			return answer;
		}
		x_n = exp(pow(U(0,1),2));
		s2 = ((n-1.0)/n)*s2 + (pow(x_n - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + x_n)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;
	}
	
}



int main(){
	srand(initial_seed);
	
	struct s_triplet answer = p8_6();
	printf("%s%d\n","Number of Samples Taken: ",answer.n);
	printf("%s%f\n","Value of Integral: ",answer.mean);
}

/*
Output:
Number of Samples Taken: 2301
Value of Integral: 1.475914
*/

/*
Discussion:
Nothing more to add compared to the prior question.
*/