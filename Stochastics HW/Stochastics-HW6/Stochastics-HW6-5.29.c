//Problem 5.29:
#include "stochastics.h"

int p5_29_poisson(){
	double t = 0; int arrivals = 0; int time_end = 1; double l = 5;
	t = t + (-1.0/l)*log(U(0,1));
	while (t < time_end){
		arrivals = arrivals + (int)U(20,40);
		t = t + (-1.0/l)*log(U(0,1));	
	}
	return arrivals;
}	

int main(){
	srand(initial_seed);
	printf("%s%f\n\n", "Mean # of fan arrivals of Problem 5.29 in 1 hour:\t ", E(p5_29_poisson, samples));

	samples = 10000; //Had to lower samples or else we would interger overflow into the negatives
	srand(initial_seed);
	printf("%s%f\n\n", "Variance of # of fan arrivals of Problem 5.29 in 1 hour: ", Var(p5_29_poisson, samples));

}

/*
Output:
Mean # of fan arrivals of Problem 5.29 in 1 hour:        147.518090

Variance of # of fan arrivals of Problem 5.29 in 1 hour: 4544.542802
*/

/*
Discussion:
Ended up spending way too long trying to figure out why I was getting a negative variance! Feel a bit silly...

Although, this did make me realize I had an error in my variance function, as I forgot to reset the seed after calculating E[X^2], causing
E[X]^2 to be calculated with a different set of X's. Also realized that I forgot there is a different formula for variance depending on
if it's a population or sample, fixed that too!
*/