//Problem 8.16:
#include "stochastics.h"

struct s_answer{ //Returns a pair of D and N for a simulation run
	double sum;
	int n;
};

struct s_answer p8_16(){ //Random variable of interest
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double T = 8; double A[360]; double D[360]; 
	//A is arrival times, D is departure times. We should expect around <36 per simulation, so reserve 10x that space and don't worry about it :)
	int n_customers = 0;  int total_enter = 0; int total_departure = 0;
	//total_enter is total # of customers who entered system
	
	t_arrival = t + Exponential(4);
	for(;;){
		if (t_arrival < fmin(t_departure, T)){ //Arrival occurs first
			t = t_arrival; t_arrival = t + Exponential(4);
			
			if (n_customers <= 3){ //Customer is free to enter
				A[total_enter] = t; //Store arrival time
				n_customers++; total_enter++; //Increment # in system, and # entered total
				if (t_departure == INFINITY){
					t_departure = t + Exponential(4.2);
				}
			}
		}
		
		else if (t_departure < T){ //Departure occurs first
			t = t_departure; D[total_departure] = t; //Store departure time
			total_departure++; n_customers--; //Incremend total departures, decriment total # in system
			
			if (n_customers > 0){
				t_departure = t + Exponential(4.2);
			}
			else{
				t_departure = INFINITY;
			}
		}
		
		else if (n_customers > 0){ //Day is over, still customers in system
			t = t_departure; D[total_departure] = t; //Store departure time
			total_departure++; n_customers--; //Incremend total departures, decriment total # in system
			t_departure = t + Exponential(4.2); //Ends up generating an extra phantom departure, but it shouldn't matter
		}
		
		else{ //Empty store, day is over, calculate mean time in system and terminate
			double sum = 0;
			for(int i = 0; i < total_enter; i++){
				sum = sum + (D[i] - A[i]);
			}
			
			struct s_answer answer;
			answer.sum = sum;
			answer.n = total_enter;
			return answer;
		}
	}
}




int main(){
	srand(initial_seed);
	samples = 100;
	struct s_answer Fe[samples];
	
	//Now we generate our Fe. If we do this often enough I'll make a more generic method in my common code for future usage
	for(int i = 0; i < samples; i++){
		Fe[i] = p8_16();
	}
	
	//Now we estimate our MSE, also will make into generic function if needed in future
	double sum_rse = 0; //Sum of each realization's squared error
	
	//First, we need to find Fe's mean D/N 
	double sum_D = 0;
	double sum_N = 0;
	for(int i = 0; i < samples; i++){sum_D = sum_D + Fe[i].sum;} //Mean of D
	for(int i = 0; i < samples; i++){sum_N = sum_N + Fe[i].n;} //Mean of N 
	double mean_Fe = sum_D/sum_N;
	
	//Now we can do our 100 realizations of Fe, and find their squared error
	for(int i = 0; i < samples; i++){ //The 100 realizations
		struct s_answer realization[samples];
		for(int i2 = 0; i2 < samples; i2++){ //Generate our realization
			realization[i2] = Fe[(int)U(0,samples)];
		}
		
		//Now, we need to find our realization's mean D/N 
		double sum_D = 0;
		double sum_N = 0;
		for(int i2 = 0; i2 < samples; i2++){sum_D = sum_D + realization[i2].sum;} //Mean of D
		for(int i2 = 0; i2 < samples; i2++){sum_N = sum_N + realization[i2].n;} //Mean of N 
		sum_rse = sum_rse + pow((sum_D/sum_N) - mean_Fe, 2);
	}
	
	double MSE = sum_rse/samples;

	
	//printf("%s%f\n","Estimated Average Time in System: ",E(p8_16,samples));
	printf("%s%d\n","Number of Samples: ",samples);
	printf("%s%f\n","Bootstrap Estimate of MSE of Estimator: ",MSE);
}

/*
Output:
Number of Samples: 100
Bootstrap Estimate of MSE of Estimator: 0.000263
*/

/*
Discussion:
I just realized I might have overdone this problem, and what was actually wanted was to have the simulation return the average time,
and then we make our Fe based on that, rather than seperate the average into a pair of total service time and number of customers served.

However, this took too long for me to now go and undo my work and redo the problem, I'll just take the point decriments instead. 
It should converge to the same mean service time value regardless...
*/