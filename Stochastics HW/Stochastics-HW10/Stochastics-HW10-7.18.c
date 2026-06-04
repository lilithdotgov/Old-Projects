//Problem 7.18:
/*
Discussion:
We would want to track the variables t (time), t_arrival (time of next arrival), n_toys (number of toys in the store), n_depart (# of customers
who depart without making a purchase), T (end time), lambda

The updating routine would be as follows:

1	>INITIALIZE t = 0, n_toys = 4, n_depart = 0, t_arrival = 0, T, lambda
2	>GENERATE Exponential(lambda)
3	>t_arrival = t + Exponential(lambda)
4	>IF t_arrival < T, THEN:
5	->t = t_arrival
6	->GENERATE U(0,1)
7	->IF U < 1/2, THEN n_toys = n_toys - 1
8	->ELSE IF U < 5/6 AND n_toys > 1, THEN n_toys = n_toys - 2
9	->ELSE IF n_toys > 2, THEN n_toys = n_toys - 3
10	->ELSE n_depart = n_depart + 1
11	->IF n_toys == 0, THEN n_toys = 10
12	->GOTO Line 2
13	>ELSE RETURN n_depart

*/

//Implementation:
#include "stochastics.h"

int p7_18(){ 
	double t = 0; double t_arrival = 0; double lambda = 5; double T = 100;
	int n_toys = 4; int n_depart = 0; 
	
	t_arrival = t + Exponential(lambda);
	while (t_arrival < T){
		t = t_arrival; t_arrival = t + Exponential(lambda);
		double rv = U(0,1);
		if (rv < (1.0/2.0)){ //At least one toy is always in stock, no need to check number
			n_toys = n_toys - 1;
		}
		else if ((rv < (5.0/6.0)) && (n_toys > 1)){
			n_toys = n_toys - 2;
		}
		else if (n_toys > 2){
			n_toys = n_toys - 3;
		}
		else{ //Customer can't be satisfied
			n_depart++;
		}
		
		if (n_toys == 0){ //Need to restock
			n_toys = 10;
		}
	}
	return n_depart;
}



int main(){
	srand(initial_seed);
	samples = 100000;
	printf("%s%f\n","Expected Value of Departures: ",E(p7_18,samples));

}

/*
Output:
Expected Value of Departures: 54.703130
*/