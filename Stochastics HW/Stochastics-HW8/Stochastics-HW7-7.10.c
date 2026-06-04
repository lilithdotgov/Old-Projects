//Problem 7.10:

//Part a discussion:
/*
The only difference is the addition of the variable p... not much more to write just look at my prior question answers.
*/
#include "stochastics.h"

struct s_result{ //For packagining different data types into one
	double* f_arr_1; //Arrival
	double* f_arr_2; //Departure
	int i_var;
} result;

struct s_result p7_10(){
	double t = 0; double t_arrival = 0; double t_departure_1 = INFINITY; double t_departure_2 = INFINITY; double p = 0.554;
	int n1 = 0; int n2 = 0; int N1 = 0; int N2 = 0; int N_max = 1000; int server_1 = 0; int server_2 = 0; 
	//server keeps track of which customer each server is currently serving
	double Arrival[N_max]; double Departure[N_max]; int Q1[N_max]; int Q2[N_max]; //Q keeps track of who to serve next for each queue
	
	t_arrival = Exponential(6);
	for(;;){
		if ((t_arrival == fmin(fmin(t_departure_1,t_departure_2),t_arrival)) && (N1 + N2 < N_max)){ //Arrival occurs first
			t = t_arrival; t_arrival = t + Exponential(6);
			
			if (U(0,1) < p){ 
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
	p7_10();
	
	double sum = 0;
	for(int i = 0; i < 1000; i++){
		sum = sum + (result.f_arr_2[i] - result.f_arr_1[i]);
	}
	printf("%s\t%f\n","Average time spent in system:", sum/1000);

	free(result.f_arr_1); free(result.f_arr_2);
}

/*
Output:
Average time spent in system:   1.747222
*/

/*
Discussion:
If p% of people are going to be served by server 1, then the propotion of people served by server 1 should be the exact same number on average
as the average proportion of people served by server 1 in the prior question, since that's what p is. Therefore, the average time spent in the
system should not change very much, maybe it'll increase a little.

WOW! I was completely wrong! I guess the issue arises when you get unlucky and people kept being sent more often to server 1 while server 2
twidles their thumbs and has no one to serve with an empty queue.
*/