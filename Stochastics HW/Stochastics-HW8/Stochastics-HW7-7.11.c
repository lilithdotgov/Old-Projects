//Problem 7.11:
#include "stochastics.h"

int p7_11(){ //Returns 1 if never went into negatives, 0 otherwise
	double t = 0; double t_claim = INFINITY; double money = 25000; double T_max = 365;
	
	t_claim = Exponential(10);
	for(;;){
		if (money < 0){
			return 0;
		}
		
		if (t_claim < T_max){ //Claim occurs first
			money = money + 11000*(t_claim - t) - Exponential(1.0/1000.0);
			t = t_claim; t_claim = t + Exponential(10);
		}
		else{
			return 1;
		}
	}
}

int main(){
	samples = 10000; //Otherwise takes a good minute to compute
	printf("%s\t%f\n","Probability firm stays in the green all year:", E(p7_11, samples));
}

/*
Output:
Probability firm stays in the green all year:   0.907200
*/

/*
Discussion:
Quite surprised how high the number is, was expecting more round 60%!
*/