//Problem 8.10:
#include "stochastics.h"

int Circle(){ //Random variable of interest
	double U1 = U(0,1); double U2 = U(0,1);
	if ((U1*U1 + U2*U2) < 1.0){
		return 4; //We return 4 so the expected value is exactly pi
	}
	else{
		return 0;
	}
}

struct s_answer{ //Used to package output data
	int n;
	double mean;
	double s2;
};
struct s_answer p8_10(){ 
	double s2 = 0; double mean = 0; double d = (0.1)*(0.5)*(1.0/1.96); //s2 is the sample variance 
	int n = 0; 
	
	//First need to handle the n = 1 case, which requires setting s2 = 0
	s2 = 0;
	mean = Circle();
	n++;
	
	for(int i = 0; i < 99; i++){
		double rv = Circle();
		s2 = ((n-1.0)/n)*s2 + (pow(rv - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + rv)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;

	}
	
	for(;;){
		if (sqrt(s2/n) < d){
			struct s_answer answer;
			answer.n = n;
			answer.mean = mean;
			answer.s2 = s2;
			return answer;
		}
		double rv = Circle();
		s2 = ((n-1.0)/n)*s2 + (pow(rv - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + rv)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;
	}
	
}



int main(){
	srand(initial_seed);
	samples = 1000;
	struct s_answer answer = p8_10();
	
	printf("%s%d\n","Number of Runs: ",answer.n);
	
	printf("%s%f\n","Expected Value: ",answer.mean);
	
	printf("%s%f\n","Standard Deviation of Estimator: ",sqrt(answer.s2/samples));

	printf("%s%f%s%f\n","95% Confidence Interval for Theta: ",answer.mean-1.96*sqrt(answer.s2/samples),"-",answer.mean+1.96*sqrt(answer.s2/samples));
}

/*
Output:
Number of Runs: 4141
Expected Value: 3.143202
Standard Deviation of Estimator: 0.051901
95% Confidence Interval for Theta: 3.041476-3.244929
*/

/*
Discussion:
Just reused code from prior assignments, nothing new to add other than making the random variable output 4 instead of 1 like in the book.
This way we get an expected value of exactly pi, rather than pi/4.
*/