//Problem 5.30:
#include "stochastics.h"

void p5_30_poisson(double *T, int events){
	double l = 7; //Ensures l >= l(t)
	double t = 0; 
	int i = 0;
	while (i < events){
		t = t + (-1.0/l)*log(U(0,1));	
		if (U(0,1) < (3.0 + (4.0/(t + 1.0)))/l){
			T[i] = t;
			i++;
		}
	}
}	

void p5_30_poisson_improved(double *T, int events){
	double t = 0; 
	int i = 0;
	double s1 = (-1.0/3.0)*log(U(0,1)); //Lambda = 3 distribution
	double s2U = U(0,1); //U needed for s2
	double s2 = (t + 1)*(1 - pow(s2U,0.25))/pow(s2U,0.25); //Lmabda = 4/(1 + x) distribution
	while (i < events){
		if (s1 < s2){
			t = t + s1; T[i] = t; i++; //s1 occurs sooner, so we store that time first
		}
		else{
			t = t + s2; T[i] = t; i++; //s2 occurs sooner, so we store that time first
		}
		
		if (t < s2){
			s1 = (-1.0/3.0)*log(U(0,1)); //s1 occured first, so generate a new one, keep old s2
		}
		else{
			s2U = U(0,1); //U needed for s2
			s2 = (t + 1)*(1 - pow(s2U,0.25))/pow(s2U,0.25); //s2 occured first, so generate a new one, keep old s1
		}
		//Since we don't have a check for if we already have enough events, this will always generate 1 extra event.
		//This is bad, but probably less bad than unneeded comparisons, since we already compare the state of
		//the number of events whenever we reach the top of the while-loop
	}
}	
	
int main(){
	srand(initial_seed);
	int events = 10; double T1[events];
	p5_30_poisson(T1, events);
	printf("%s\n\t", "Sequence of events in time for problem 5.30 with basic method:\t ");
	for(int i = 0; i < events; i++){
		printf("%f%s", T1[i], " ");
	}
	
	srand(initial_seed);
	events = 10; double T2[events];
	p5_30_poisson_improved(T2, events);
	printf("\n\n%s\n\t", "Sequence of events in time for problem 5.30 with improved method:\t ");
	for(int i = 0; i < events; i++){
		printf("%f%s", T2[i], " ");
	}
}

/*
Output:
Sequence of events in time for problem 5.30 with basic method:
    1.086313 1.100348 1.225802 1.832760 1.865905 1.979438 2.157962 2.435080 2.592068 2.825108

Sequence of events in time for problem 5.30 with improved method:
    0.016589 1.166336 1.383624 1.416371 2.050652 2.684933 3.259823 3.894105 4.260044 4.337384
*/

/*
Discussion:
For my improved algorithm I attempted to find the inverse of Fs, the distribution of the additional time until next event.

I wasted a good while trying to find an inverse for Fs(x), but lambda(t) = 3 + 4/(t+1) gives you an awful expression when integrating and doing
the rest of the work. So, I then tried again by generating two poisson processes of l(t) = 3 and l(t) = 4/(t+1), and combining them together.
This worked much better!
*/