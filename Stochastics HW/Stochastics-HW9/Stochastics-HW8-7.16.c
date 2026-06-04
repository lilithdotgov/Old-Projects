//Problem 7.16:
#include "stochastics.h"

double Weather(double t){ //Function that determine the time a message "clogs" the system
	if (fmod((t + 1),3) < 1){ //Weather is bad
		return pow(U(0,1),1.0/3.0);
	}
	else{ //Weather is good
		return U(0,1);
	}
}

int p7_16(){
	double t = 0; double t_arrival; double T = 100;
	double t_departue_1 = INFINITY; double t_departue_2 = INFINITY; double t_departue_3 = INFINITY;
	int lost = 0;
	
	t_arrival = t + Exponential(2);
	for(;;){
		if (t_arrival < fmin(fmin(fmin(t_departue_1, t_departue_2), t_departue_3), T)){
			t = t_arrival; t_arrival = t + Exponential(2);
			
			if (t_departue_1 == INFINITY){
				t_departue_1 = t + Weather(t);
			}
			else if (t_departue_2 == INFINITY){
				t_departue_2 = t + Weather(t);
			}
			else if (t_departue_3 == INFINITY){
				t_departue_3 = t + Weather(t);
			}
			else{ //All servers are busy, message is lost
				lost++;
			}
		}
		else if (t_departue_1 < fmin(fmin(t_departue_2, t_departue_3), T)){
			t = t_departue_1; t_departue_1 = INFINITY;
		}
		else if (t_departue_2 < fmin(t_departue_3, T)){
			t = t_departue_2; t_departue_2 = INFINITY;
		}
		else if (t_departue_3 < T){
			t = t_departue_3; t_departue_3 = INFINITY;
		}
		else{
			return lost;
		}
	}
}


int main(){
	srand(initial_seed);
	samples = 100000;
	printf("%s%f\n","Expected Value of Lost Messages: ",E(p7_16,samples));

}

/*
Output:
Expected Value of Lost Messages: 17.287500
*/

/*
Discussion:
It's starting to feel like we might be reaching the point where a more elegant method like an array of departure times and switch statements
would be better for the sake of efficiency. This works too though.
*/