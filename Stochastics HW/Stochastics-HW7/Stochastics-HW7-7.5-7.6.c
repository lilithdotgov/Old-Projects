//Problem 7.5:

/*
Discussion:
The variables we'd need are t_arrival for time of next arrival, t_departure for time of next departure, t_defeated for time
of next customer being "defeated" and leaving the queue, Defeated[] to store a list of sequential defeated times for each customer,
indexed by the customer number in order of appearance, and n for current number of customers in system.

The main thing we'd care about is having two methods to analyze the Defeated[] list. One to find when the soonest defeat is and set_new_handler
t_defeated to that, and another to find which defeated corresponds to the current customer being served (so as to ensure they don't leave 
while being served). If a customer is being served, or is defeated, we set their defeat time in the list to Infinity. 

For updates, everytime we generate a new arrival we should assign that person a defeat time, and add it to the list, then update to
find the soonest defeat time. 

Every departure corresponds to a new person being served, and since our queue is First-In First-Out, we 
just need to find the first non-Infinity element in our list, this will correspond to the defeat time of the person being served. 
We then set that defeat time to infinity, and run our method again to find the soonest defeat time and update t_defeated if needed.

Every time a customer is defeated, we substract 1 from n, find their time in the list and set it to Infinity, and once more find
what the soonest defeat is and set t_defeated to that, then continue. Everything else stays roughly the same as would be expected.
*/

//Problem 7.6:
#include "stochastics.h"

int p7_6_defeated(){ //"Defeated" in the sense that the customer gives up and leaves the queue
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double t_defeated = INFINITY; 
	double T_end = 100; double Defeated[10000]; double min = INFINITY;
	int n = 0; int N = 0; int t_defeated_total = 0; int index_defeated = 0;
	//t_defeated will be the soonest instance of a customer leaving, while Defeated is a list of all instances

	t_arrival = t + (-1.0/5.0)*log(U(0,1)); //Generate our first arrival
	Defeated[N] = INFINITY; //Set first defeated to INFINITY since they will be served immedietly
	
	int test = 0;
	for(;;){
		
		
		//fmin and fmax can't take more than two arguments, so need to nest them, kinda awful but oh well!
		if (t_arrival < fmin(fmin(t_departure, t_defeated), T_end)){
			t = t_arrival; n = n + 1; N = N + 1;
			printf("%s%f\n","Arrival at t = ",t);

			t_arrival = t + (-1.0/5.0)*log(U(0,1)); //Generate our next arrival
			Defeated[N] = t_arrival + U(0,5);//Generates defeated time for next arrival
			if (Defeated[N] < t_defeated){ //Sets t_defeated to new time if new time is earlier
				t_defeated = Defeated[N];
				printf("%s%f\n","Next Defeat at t = ",t_defeated);
				index_defeated = N; //Sets index to soonest defeat in case we don't serve in time and need to remove from list
			}
			
			
			if (n == 1){ //Went from 0 to 1 customer, need new departure time
				t_departure = t + (-1.0/4.0)*log(U(0,1));
			}
		}
		
		else if (t_departure < fmin(fmin(t_arrival, t_defeated), T_end)){
			t = t_departure; n = n - 1;
			printf("%s%f\n","Departure at t = ",t);
			if (n > 0){
				t_departure = t + (-1.0/25.0)*log(U(0,1));
				printf("%s%f\n","Next departure at t = ",t_departure);
			}
			
			//Find index of first non-INFINITY element, this tells us who is being served and so should be removed from defeated list
			int i = 0;
			for(;;){
				if (Defeated[i] < INFINITY){
					break;
				}
				i++;
			}
			int index_temp = i;
			
			if (Defeated[i] == t_defeated){ //If we remove the soonest defeat time, we need to find the next one first
				printf("%s%d\n","Comparison was a success at N = ",N);
				Defeated[index_temp] = INFINITY; //Set to infinity to indicate they will never leave out of defeat
				
				//Find when the next soonest defeated is and at what index
				int i = 0; min = INFINITY; index_defeated = 0;
				
				for(;;){
					if (Defeated[i] == 0){
						break;
					}
					else if (Defeated[i] < min){
						min = Defeated[i];
						index_defeated = i;
					}
					i++;
				}
				t_defeated = min;
				
			}
			else{
				Defeated[index_temp] = INFINITY; //Set to infinity to indicate they will never leave out of defeat
			}
			
			printf("%d\t%f\n",index_defeated, t_defeated);
			
		}
		
		else if (t_defeated < fmin(fmin(t_departure, t_arrival), T_end)){ //We get a defeated customer before any other event
			t = t_defeated; n = n - 1; t_defeated_total = t_defeated_total + 1; Defeated[index_defeated] = INFINITY;
			
			printf("%s%f\n","Defeat at t = ",t);
			printf("%s%d\n","index_defeated = ",index_defeated);
			printf("%s%f\n","Defeated[index_defeated] = ",Defeated[index_defeated]);
			
			//Find when the next soonest defeated is and at what index
			int i = 0; min = INFINITY; index_defeated = 0;
			
			for(;;){
				if (Defeated[i] == 0){
					break;
				}
				else if (Defeated[i] < min){
					min = Defeated[i];
					index_defeated = i;
				}
				i++;
			}
			t_defeated = min;
			
			printf("%s%f\n","next Defeat at t = ",t_defeated);
			
		}
		
		else if (T_end < fmin(t_arrival, t_departure)){ //Don't care about overtime, ends as soon as t = T_end
			return t_defeated_total;
		}
		
		if (test == 10){
			return 0;
		}
		test++;
	}
}

int main(){
	srand(initial_seed);
	samples = 500;
	printf("%s%d\n\n", "Mean of Problem 7.6 Random Variable: ", p7_6_defeated()); //Sanity check
	//printf("%s%f\n\n", "Mean of Problem 7.6 Random Variable: ", E(p7_6_defeated, samples)); //Sanity check
}

/*
Output:
:(
*/

/*
Discussion:
Look upon my works, ye mighty, and despair! For I have been feeling very ill and with little time or energy to work on this assignment, and so
I didn't get to finish this problem... 
Above is some poorly written code that doesn't even work (you can see me try and debug it and fail to do so).
Question 3 also has some poorly written code that I would've rewrote to be less insane had I the ability to do so right now.

Oh well, better to submit SOMETHING rather than be left empty-handed! 
*/