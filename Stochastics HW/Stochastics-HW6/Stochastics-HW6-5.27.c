//Problem 5.27:
#include "stochastics.h"

void p5_27_poisson(double *T, int events, double l){
	double t = 0; 
	for(int i = 0; i < events; i++){
		t = t + (-1.0/l)*log(U(0,1));	
		T[i] = t;
	}
}	
	
int main(){
	srand(initial_seed);
	int events = 20; double T[events]; double l = 0.5;
	p5_27_poisson(T, events, l);
	printf("%s\n\t", "Sequence of events in time for problem 5.27: ");
	for(int i = 0; i < events; i++){
		printf("%f%s", T[i], " ");
	}
}

/*
Output:
Sequence of events in time for problem 5.27:
    6.898480 7.030102 15.340010 16.643740 16.840223 20.645909 22.402262 23.562064 32.059482 34.255120 34.719156 37.336035 38.925490 45.979737 
	47.201645 47.358260 48.635691 50.341426 53.168650 53.497926
*/

/*
Discussion:
I don't know how best to deal with data storage and am conflicted between automatic and dynamic arrays. Oh well, it's probably fine for such
a basic example.
*/