//Problem 7.9:

//Part a discussion:
/*
Ignoring the variables that stay the same, we'd need to add 2 arrays, Q1 and Q2, to keep track of each queue and who is in it.
n would be replaced with n1 and n2 for the number of people in each queue (plus whoever is being served).
We can remove the array that keeps track of which server each customer went to, since Q1 and Q2 provide that info already.
Another thing of note: we previously kept track of which person each server was serving, and assigned each person a number
based on when they entered the system. Instead, we will assign them a number based on when they entered each queue. This will
be tracked by server_1 and server_2, for queue 1 and 2 respectively. And N1 and N2 will be the total number of people to enter that
queue. 

All together, this allows us to query Q1/2 based on the index from server_1/2, obtaining us the index of when this person arrived
(i.e. are they the 20th person to arrive in the system? So we can then index them in Departure appropriatly)

Worth stating that n = n1 + n2, and N = N1 + N2.

As for updates, view the code below:
*/
#include "stochastics.h"

struct s_result{ //For packagining different data types into one
	double* f_arr_1; //Arrival
	double* f_arr_2; //Departure
	int i_var;
} result;

struct s_result p7_9(){
	double t = 0; double t_arrival = 0; double t_departure_1 = INFINITY; double t_departure_2 = INFINITY;
	int n1 = 0; int n2 = 0; int N1 = 0; int N2 = 0; int N_max = 1000; int server_1 = 0; int server_2 = 0; 
	//server keeps track of which customer each server is currently serving
	double Arrival[N_max]; double Departure[N_max]; int Q1[N_max]; int Q2[N_max]; //Q keeps track of who to serve next for each queue
	
	t_arrival = Exponential(6);
	for(;;){
		if ((t_arrival == fmin(fmin(t_departure_1,t_departure_2),t_arrival)) && (N1 + N2 < N_max)){ //Arrival occurs first
			t = t_arrival; t_arrival = t + Exponential(6);
			
			if (n1 <= n2){ //Queue 1 is shorter or equal in size
				n1++; N1++; Arrival[N1+N2-1] = t;
				if (t_departure_1 == INFINITY){ //Server 1 is free
					t_departure_1 = t + Exponential(4);
					server_1++; Q1[server_1-1] = N1 + N2;
					//Server sees next person, so server_1 increases by one. Q1 indexed by next person, Nth in system added
				}
				else{
					Q1[N1-1] = N1 + N2;
					//We already have people in line, so we look at the total number of people that have arrived so far for index
				}
			}
			else{
				n2++; N2++; Arrival[N1+N2-1] = t;
				if (t_departure_2 == INFINITY){ //Server 1 is free
					t_departure_2 = t + Exponential(3);
					server_2++; Q2[server_2-1] = N1 + N2;
					//Server sees next person, so server_1 increases by one. Q1 indexed by next person, Nth in system added
				}
				else{
					Q2[N2-1] = N1 + N2;
					//We already have people in line, so we look at the total number of people that have arrived so far for index
				}
			}
		}
		else if (t_departure_1 <= t_departure_2){ //Server 1 finishes first
			t = t_departure_1; n1--; Departure[Q1[server_1-1]-1] = t;
			
			if (n1 == 0){ //No one in queue
				t_departure_1 = INFINITY;
			}
			else{
				t_departure_1 = t + Exponential(4); 
				server_1++;
			}
		}
		else{ //Server 2 finishes first
			t = t_departure_2; n2--; Departure[Q2[server_2-1]-1] = t;
			
			if (n2 == 0){ //No one in queue
				t_departure_2 = INFINITY;
			}
			else{
				t_departure_2 = t + Exponential(3); 
				server_2++;
			}
		}
		
		if ((N1 + N2 == N_max) && (n1 + n2 == 0)){ //Reached 1000th person AND served everyone left in the system 
			//Packaging data before it is sent:
			result.i_var = N1;
			result.f_arr_1 = malloc(sizeof Arrival);
			result.f_arr_2 = malloc(sizeof Departure);
			memcpy(result.f_arr_1, Arrival, sizeof Arrival);
			memcpy(result.f_arr_2, Departure, sizeof Departure);

			return result;
		}
	}
}


int main(){
	srand(initial_seed);
	p7_9();
	
	double sum = 0;
	for(int i = 0; i < 1000; i++){
		sum = sum + (result.f_arr_2[i] - result.f_arr_1[i]);
	}
	printf("%s\t%f\n","Average time spent in system:", sum/1000);
	

	printf("%s\t%f\n\n","Proportion of services performed by server 1:",result.i_var/1000.0);

	free(result.f_arr_1); free(result.f_arr_2);
}

/*
Output:
Average time spent in system:   0.824322
Proportion of services performed by server 1:   0.554000
*/

/*
Discussion:
I expect almost no change in the proportion figure, but would understand if this lowered the average wait time by around 10-25%.

Not going to lie, with just n = 1 samples of this system and only n = 2 samples of the prior, I can't tell if anything meaningfully changed.
So, no clue if my prediction is accurate. Odd that the book doesn't ask for expected value or variability.

This question was a pain because I was dumb with the indexing for the Q's, I think it's the same problem I had on the prior homework which
I had given up on due to time constraints. Glad I could resolve it this time!
*/