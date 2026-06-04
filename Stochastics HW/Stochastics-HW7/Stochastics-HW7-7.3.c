//Problem 7.3:
#include "stochastics.h"

double p7_3_break(){
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double t_break = 0; 
	double t_break_total = 0; double t_break_flag = INFINITY; double T_end = 100; double l = 0; double lmax = 19;
	int n = 0;
	//Note that t_break_flag is INFINITY at beginning, since the question specifies a break occurs only AFTER a service is done.

	t_arrival = t;
	for(;;){ //Generates our t_arrival, pretty bad method though, but it's easy to implement
		t_arrival = t_arrival + (-1.0/lmax)*log(U(0,1));
		l = -abs(3.0*(fmod(t_arrival,10.0) - 5.0)) + 19.0; //Modulo makes lambda(t) periodic very cleanly
		if (U(0,1) < (l/lmax)){
			break;
		}
	}
	
	for(;;){
		//fmin and fmax can't take more than two arguments, so need to nest them, kinda awful but oh well!
		if (t_arrival < fmin(fmin(t_departure, t_break_flag), T_end)){
			t = t_arrival; n = n + 1; 
			
			for(;;){ //Generates our t_arrival, pretty bad method though, but it's easy to implement
				t_arrival = t_arrival + (-1.0/lmax)*log(U(0,1));
				l = -abs(3.0*(fmod(t_arrival,10.0) - 5.0)) + 19.0; //Modulo makes lambda(t) periodic very cleanly
				if (U(0,1) < (l/lmax)){
					break;
				}
			}
			
			if (n == 1){ //Went from 0 to 1 customer, need new departure time
				t_departure = t + (-1.0/25.0)*log(U(0,1));
			}
		}
		
		else if (t_departure < fmin(fmin(t_arrival, t_break_flag), T_end)){
			t = t_departure; n = n - 1;
			if (n > 0){
				t_departure = t + (-1.0/25.0)*log(U(0,1));
			}
			else{ //No customers left, no need for a new departure time
				t_departure = INFINITY;
				t_break_flag = -1; //Sets the flag to -1, so all activities are skipped until break is over
				t_break = t + U(0,0.3); //Sets time when break finishes
				t_break_total = t_break_total + fmin(t_break - t, T_end - t); //Stores the time spent on break. 
				//Also, fmin is needed to account for break ending after T_end
			}
		}
		
		else if (t_break_flag < fmin(t_arrival, t_departure)){ //Break is currently occuring
			
			while (t_break < fmin(t_arrival, T_end)){ //Checks for sequential breaks
				t_break = t + U(0,0.3); //Sets time when break finishes
				t_break_total = t_break_total + fmin(t_break - t, T_end - t);//Stores the time spent on break.
				//Also, fmin is needed to account for break ending after T_end
				
				t = t_break; //Moves time to next break		
			}
			
			while (t_arrival < fmin(t_break, T_end)){ //Accounts for arrivals occuring during break
				t = t_arrival; n = n + 1; //Sets time to arrival, very important!
				
				for(;;){ //Generates our t_arrival, pretty bad method though, but it's easy to implement
					t_arrival = t_arrival + (-1.0/lmax)*log(U(0,1));
					l = -abs(3.0*(fmod(t_arrival,10.0) - 5.0)) + 19.0; //Modulo makes lambda(t) periodic very cleanly
					if (U(0,1) < (l/lmax)){
						break;
					}
				}
				//We do this generation to see if more arrivals occur during the break
			}
			
			t = t_break; //Arrivals are done, so now set time to end of break
			t_break_flag = INFINITY; //Regular operation resumes, no more breaks
			t_departure = t + (-1.0/25.0)*log(U(0,1)); //Generate next departure since we can start processing tasks again
		}
		
		else if (T_end < fmin(t_arrival, t_departure)){ //Don't care about overtime, ends as soon as t = T_end
			return t_break_total;
		}
	}
}

int main(){
	srand(initial_seed);
	samples = 500;
	printf("%s%f\n\n", "Mean of Problem 7.3 Random Variable: ", E(p7_3_break, samples)); //Sanity check
}

/*
Output:
Mean of Problem 7.3 Random Variable: 58.619386
*/

/*
Discussion:
I decided to use a flag variable to handle the case when the system is in break. This is technically not neccessary since you could just have this
case be a part of the departure case, however, this makes the code a bit more legible in my opinion, at least compared to stuffing all of the 
break code inside the departure code. 

I've used the basic method of generating non-homogenous poisson processes, this is not optimal but is much easier to implement than keeping track
of multiple generated lambda as would occur if the distribution was to be split between 3 different distributions that we can find inverses of.

The book does mention another method that is more optimal, but I cannot understand WHY it works, and so I don't wish to implement it if I have no
grasp on how it functions. Subdividing the interval just seems like it would not work??? I'll maybe ask sometime after class about it if I don't
forget.

Otherwise, the main difficulty is in accounting for the case in which we have repeated breaks or if arrivals occur during the break, as well as
making sure that we don't add extra break time at the end if the end time is reached before the break ends. Most of the rest of the code stays
the same.
*/