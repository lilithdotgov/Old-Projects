//Problem 7.8:
#include "stochastics.h"

struct s_result{ //For packagining different data types into one
	double* f_arr_1;
	double* f_arr_2;
	int* i_arr;
} result;

struct s_result p7_8(){
	double t = 0; double t_arrival = 0; double t_departure_1 = INFINITY; double t_departure_2 = INFINITY;
	int n = 0; int N = 0; int N_max = 1000; int server_1 = 0; int server_2 = 0; 
	//server keeps track of which customer each server is currently serving
	double Arrival[N_max]; double Departure[N_max]; int Server[N_max]; //Server tracks which customer was server by each server
	
	t_arrival = Exponential(6);
	for(;;){
		if ((t_arrival == fmin(fmin(t_departure_1,t_departure_2),t_arrival)) && (N < N_max)){ //Arrival occurs first
			t = t_arrival; n++; N++; Arrival[N-1] = t; 
			t_arrival = t + Exponential(6);
			
			if (t_departure_1 == INFINITY){ //Server 1 is free
				t_departure_1 = t + Exponential(4);
				server_1 = N; Server[N-1] = 1;
			}
			else if (t_departure_2 == INFINITY){ //Server 2 is free
				t_departure_2 = t + Exponential(3);
				server_2 = N; Server[N-1] = 2;
			}
			
		}
		else if (t_departure_1 <= t_departure_2){ //Server 1 finishes first
			t = t_departure_1; n--; Departure[server_1-1] = t;
			
			if (n <= 1){ //No one in queue
				t_departure_1 = INFINITY; server_1 = 0;
			}
			else{
				t_departure_1 = t + Exponential(4); 
				server_1 = (int)fmax(server_1,server_2) + 1; Server[server_1-1] = 1;
			}
		}
		else{ //Server 2 finishes first
			t = t_departure_2; n--; Departure[server_2-1] = t;
			
			if (n <= 1){ //No one in queue
				t_departure_2 = INFINITY; server_2 = 0;
			}
			else{
				t_departure_2 = t + Exponential(3); 
				server_2 = (int)fmax(server_1,server_2) + 1; Server[server_2-1] = 2;
			}
		}
		
		if ((N == N_max) && (n == 0)){ //Reached 1000th person AND served everyone left in the system 
			//Packaging data before it is sent:
			result.i_arr = malloc(sizeof Server);
			result.f_arr_1 = malloc(sizeof Arrival);
			result.f_arr_2 = malloc(sizeof Departure);
			memcpy(result.i_arr, Server, sizeof Server);
			memcpy(result.f_arr_1, Arrival, sizeof Arrival);
			memcpy(result.f_arr_2, Departure, sizeof Departure);

			return result;
		}
	}
}


int main(){
	//First simulation
	printf("%s\n","First simulation of part a and b:");
	srand(initial_seed);
	p7_8();
	
	double sum = 0;
	for(int i = 0; i < 1000; i++){
		sum = sum + (result.f_arr_2[i] - result.f_arr_1[i]);
	}
	printf("%s\t%f\n","Average time spent in system:", sum/1000);
	
	int count = 0;
	for(int i = 0; i < 1000; i++){
		if (result.i_arr[i] == 1){count++;}
	}
	printf("%s\t%f\n\n","Proportion of services performed by server 1:",count/1000.0);
	
	//Secon simulation
	printf("%s\n","Second simulation of part a and b:");
	srand(2707); //New seed for part c
	p7_8();
	
	sum = 0;
	for(int i = 0; i < 1000; i++){
		sum = sum + (result.f_arr_2[i] - result.f_arr_1[i]);
	}
	printf("%s\t%f\n","Average time spent in system:", sum/1000);
	
	count = 0;
	for(int i = 0; i < 1000; i++){
		if (result.i_arr[i] == 1){count++;}
	}
	printf("%s\t%f\n\n","Proportion of services performed by server 1:",count/1000.0);
	free(result.i_arr); free(result.f_arr_1); free(result.f_arr_2);
}

/*
Output:
First simulation of part a and b:
Average time spent in system:   0.844763
Proportion of services performed by server 1:   0.589000

Second simulation of part a and b:
Average time spent in system:   0.804140
Proportion of services performed by server 1:   0.579000
*/

/*
Discussion:
It seems both results are roughly the same with not much variation in the average time nor the proportionality of serving.


*/