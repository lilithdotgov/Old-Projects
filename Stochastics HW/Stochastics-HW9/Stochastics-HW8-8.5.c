//Problem 8.5:
#include "stochastics.h"

/*
Part a discussion:
Since we know the distribution's actual SD, which is 1, and n is sufficiently large, then we can just say 
1/sqrt(n) < 1/100. Which implies we need approximately 100^2 = 10000 samples to reduce our variability from the 
true mean to a SD of 1/100.  
*/

struct s_triplet{ //Used to package output data
	int n;
	double mean;
	double s2;
};

struct s_triplet p8_5(){ 
	double s2 = 0; double mean = 0; double d = 0.01; //s2 is the sample variance 
	int n = 0; struct s_tuple tuple;
	
	//First need to handle the n = 1 case, which requires setting s2 = 0
	tuple = Gaussian();
	//First value:
	s2 = 0;
	mean = tuple.t1;
	n++;
	
	//Second value:
	s2 = ((n-1.0)/n)*s2 + (pow(tuple.t2 - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
	mean = ((n*mean + tuple.t2)/(n+1.0)); //Now the mean is updated for the n+1'th term
	n++;
	
	for(int i = 0; i < 49; i++){ //Only does 50 runs since we generate two values each time
		tuple = Gaussian(); //Generate our two values
		//We then update mean and variance one value at a time
		s2 = ((n-1.0)/n)*s2 + (pow(tuple.t1 - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + tuple.t1)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;
		
		
		//Second value
		s2 = ((n-1.0)/n)*s2 + (pow(tuple.t2 - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + tuple.t2)/(n+1.0)); //Now the mean is updated for the n+1'th term
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
		tuple = Gaussian(); //Generate our two values
		//We then update mean and variance one value at a time
		s2 = ((n-1.0)/n)*s2 + (pow(tuple.t1 - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + tuple.t1)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;
		
		
		//Second value
		s2 = ((n-1.0)/n)*s2 + (pow(tuple.t2 - mean,2)/(n+1.0)); //s2 uses the n'th mean value, so we update it first
		mean = ((n*mean + tuple.t2)/(n+1.0)); //Now the mean is updated for the n+1'th term
		n++;
	}
	
}



int main(){
	srand(initial_seed);
	
	struct s_triplet answer = p8_5();
	printf("%s%d\n","Number of Normals Generated: ",answer.n);
	printf("%s%f\n","Mean of Normals Generated: ",answer.mean);
	printf("%s%f\n","Variance of Normals Generated: ",answer.s2);
	
}

/*
Output:
Number of Normals Generated: 10050
Mean of Normals Generated: -0.009160
Variance of Normals Generated: 1.004876
*/

/*
Discussion:
Pretty straight-forward approach to the problem. We use the recusive algorithms for mean and variance rather than compute it in full every single
loop, or guess at how many samples we'd need and over-generate them (not that this would be actually a bad appraoch for a problem like this where
we know the SD of the distribution, but still, in general this seems worse).

The sample mean and sample variance don't seem surprising at all, that's just about what I'd expect from a normal distribution.
*/