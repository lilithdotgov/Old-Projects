//Lilith Janevska, Stochastic Simulation HW12

//Common Code:
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int initial_seed = 307;
int samples = 1000000;

#define E(x, y) _Generic((x), int (*)(void): E_i, double (*)(void): E_d)(x, y)
#define Var(x, y) _Generic((x), int (*)(void): Var_i, double (*)(void): Var_d)(x, y)
#define Time(x, y) _Generic((x), int (*)(void): Time_i, double (*)(void): Time_d)(x, y)

double U(double min_val, double max_val){ //Gives a random double between max_val to min_val
	double u = (max_val - min_val)*(((float)rand())/RAND_MAX) + min_val;
	while ((u == min_val) || (u == max_val)){
		u = (max_val - min_val)*(((float)rand())/RAND_MAX) + min_val;
	}
	
	return u;
}

double E_i(int (*f)(void), double samples){ //Gives the Expected Value of a given Random Variable
	srand(initial_seed);
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + (*f)();
	}
	
	return (double)sum/samples;
}

double E_d(double (*f)(void), double samples){ //Gives the Expected Value of a given Random Variable
	srand(initial_seed);
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + (*f)();
	}
	
	return (double)sum/samples;
}

double Var_i(int (*f)(void), double samples){ //Gives the Variance of a given Random Variable
	srand(initial_seed);
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + pow((double)(*f)(),2.0);
	}
	srand(initial_seed);
	return (sum/(samples - 1)) - pow((samples/(samples - 1))*E(f,samples),2.0);
}

double Var_d(double (*f)(void), double samples){ //Gives the Variance of a given Random Variable
	srand(initial_seed);
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + pow((double)(*f)(),2.0);
	}
	srand(initial_seed);
	return (sum/(samples - 1)) - pow((samples/(samples - 1))*E(f,samples),2.0);
}


void Permute(int *array, int length){ //Permutes an array of elements
	for(int i = length - 1; i >= 1; i--){
		int P = (i + 1)*U(0,1);
		int temp = array[P];
		array[P] = array[i];
		array[i] = temp;
	}
}

double Time_i(int (*f)(void), int samples){ // Gives the average execution time of a function in ns
	clock_t begin = clock();
	for(int i =  0; i < samples; i++){
		(*f)();
	}
	clock_t end = clock();
	return (double)(end - begin) / (CLOCKS_PER_SEC * samples / 1000000000);
}

double Time_d(double (*f)(void), int samples){ // Gives the average execution time of a function in ns
	clock_t begin = clock();
	for(int i =  0; i < samples; i++){
		(*f)();
	}
	clock_t end = clock();
	return (double)(end - begin) / (CLOCKS_PER_SEC * samples / 1000000000);
}

//Distributions:

double Exponential(double lambda){
	return (-1.0/lambda)*log(U(0,1));
}


double Binomial(double n, double p){
	double rv = U(0,1);
	double P = pow(1 - p, n);
	double P_tot = P;
	int i = 0;
	while (P_tot < rv){
		P = ((n - i)/(i + 1))*(p/(1 - p))*P;
		P_tot = P_tot + P;
		i++;
	}
	
	return i;
}

double Poisson(double l){
	double rv = U(0,1);
	double P = exp(-l);
	double P_tot = P;
	int i = 0;
	while (P_tot < rv){
		P = (l/(i+1))*P;
		P_tot = P_tot + P;
		i++;
	}
	
	return i;
}

struct s_tuple{ //For packaging the two Gaussian outputs
	double t1; 
	double t2;
};

struct s_tuple Gaussian(){
	struct s_tuple tuple;
	double u1 = U(-1,1); double u2 = U(-1,1); double s = u1*u1 + u2*u2;
	for(;;){
		if (s < 1){
			tuple.t1 = (sqrt((-2*log(s))/s))*u1;
			tuple.t2 = (sqrt((-2*log(s))/s))*u2;
			return tuple;
		}
		u1 = U(-1,1); u2 = U(-1,1); s = u1*u1 + u2*u2;
	}
}
//End of Common Code
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
