//Problem 9.24:
#include "stochastics.h"


double p9_24_a(){ //Random variable of interest
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double A[10]; double D[10];
	int n = 0; int N = 0; int N_end = 10;
	
	t_arrival = t + Exponential(2);
	for(;;){
		if ((t_arrival < t_departure) && (N < N_end)){ //Arrival occurs first and we haven't reached our 10th customer
			t = t_arrival; t_arrival = t + Exponential(2); A[N] = t;
			if (n == 0){
				t_departure = t + Exponential(1);
			}
			n++; N++;
		}
		
		else if (n > 0){ //Departure occurs first and there's people in the system left
			t = t_departure; D[N-n] = t; n--;
			
			if (n > 0){
				t_departure = t + Exponential(1);
			}
			else{
				t_departure = INFINITY;
			}
		}
		
		else{ //End of simulation, count up times
			double sum = 0;
			for(int i = 0; i < 10; i++){
				sum = sum + D[i] - A[i];
			}
			return sum;
		}
	}
}

double p9_24_b(){ //Again but with antithetics
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double A[10]; double D[10];
	int n = 0; int N = 0; int N_end = 10;
	
	double U_a[10]; double U_d[10]; int i_a = 0; int i_d = 0; //i's track which U has been used already
	//Set up each array of U's we'll need
	double rv;
	for(int i = 0; i < 10; i++){
		if ((i % 2) == 0){
			rv = U(0,1);
			U_a[i] = rv;
		}
		else{
			U_a[i] = 1 - rv;
		}
	}
	for(int i = 0; i < 10; i++){
		if ((i % 2) == 0){
			rv = U(0,1);
			U_d[i] = rv;
		}
		else{
			U_d[i] = 1 - rv;
		}
	}
	
	t_arrival = t + (-1.0/2.0)*log(U_a[i_a]); i_a++;
	for(;;){
		if ((t_arrival < t_departure) && (N < N_end)){ //Arrival occurs first and we haven't reached our 10th customer
			t = t_arrival; t_arrival = t + (-1.0/2.0)*log(U_a[i_a]); i_a++; A[N] = t;
			if (n == 0){
				t_departure = t + (-1.0)*log(U_d[i_d]); i_d++;
			}
			n++; N++;
		}
		
		else if (n > 0){ //Departure occurs first and there's people in the system left
			t = t_departure; D[N-n] = t; n--;
			
			if (n > 0){
				t_departure = t + (-1.0)*log(U_d[i_d]); i_d++;
			}
			else{
				t_departure = INFINITY;
			}
		}
		
		else{ //End of simulation, count up times
			double sum = 0;
			for(int i = 0; i < 10; i++){
				sum = sum + D[i] - A[i];
			}
			return sum;
		}
	}
}

double c;
double mu;
//Mutable global variables are evil but I'm lazy

struct s_answer{
	double X;
	double Y;
};

struct s_answer p9_24_c(){ //Again with control variates
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double A[10]; double D[10];
	int n = 0; int N = 0; int N_end = 10;
	
	double tot_service = 0;
	
	t_arrival = t + Exponential(2);
	for(;;){
		if ((t_arrival < t_departure) && (N < N_end)){ //Arrival occurs first and we haven't reached our 10th customer
			t = t_arrival; t_arrival = t + Exponential(2); A[N] = t;
			if (n == 0){
				t_departure = t + Exponential(1); 
				tot_service = tot_service + (t_departure - t); //Get our Si
			}
			n++; N++;
		}
		
		else if (n > 0){ //Departure occurs first and there's people in the system left
			t = t_departure; D[N-n] = t; n--;
			
			if (n > 0){
				t_departure = t + Exponential(1);
				tot_service = tot_service + (t_departure - t); //Get our Si
			}
			else{
				t_departure = INFINITY;
			}
		}
		
		else{ //End of simulation, count up times
			double sum = 0;
			for(int i = 0; i < 10; i++){
				sum = sum + D[i] - A[i];
			}
			struct s_answer answer;
			answer.X = sum;
			answer.Y = tot_service;
			return answer;
		}
	}
}

double X_c(){ //Our variable of interest of part c
	return p9_24_c().X;
}

double Y_c(){ //Control variable of part c
	return p9_24_c().Y;
}

double CV_c(){ //Uses the control variate to get X
	struct s_answer answer = p9_24_c();
	double X = answer.X; double Y = answer.Y;
	return X + c*(Y - mu);
}

struct s_answer p9_24_d(){ //Again with new control variates
	double t = 0; double t_arrival = 0; double t_departure = INFINITY; double A[10]; double D[10];
	int n = 0; int N = 0; int N_end = 10;
	
	double tot_service = 0;
	
	t_arrival = t + Exponential(2);
	for(;;){
		if ((t_arrival < t_departure) && (N < N_end)){ //Arrival occurs first and we haven't reached our 10th customer
			t = t_arrival; t_arrival = t + Exponential(2); A[N] = t;
			if (n == 0){
				t_departure = t + Exponential(1); 
				tot_service = tot_service + (t_departure - t); //Get our Si
			}
			n++; N++;
		}
		
		else if (n > 0){ //Departure occurs first and there's people in the system left
			t = t_departure; D[N-n] = t; n--;
			
			if (n > 0){
				t_departure = t + Exponential(1);
				tot_service = tot_service + (t_departure - t); //Get our Si
			}
			else{
				t_departure = INFINITY;
			}
		}
		
		else{ //End of simulation, count up times
			double sum = 0;
			for(int i = 0; i < 10; i++){
				sum = sum + D[i] - A[i];
			}
			
			double sum2 = 0;
			for(int i = 0; i < 9; i++){
				sum2 = sum2 + (A[i+1] - A[i]);
			}
			
			struct s_answer answer;
			answer.X = sum;
			answer.Y = tot_service - sum2;
			return answer;
		}
	}
}

double X_d(){ //Our variable of interest of part d
	return p9_24_d().X;
}

double Y_d(){ //Control variable of part d
	return p9_24_d().Y;
}

double CV_d(){ //Uses the control variate to get X
	struct s_answer answer = p9_24_d();
	double X = answer.X; double Y = answer.Y;
	return X + c*(Y - mu);
}

int main(){
	samples = 10000;
	//Part a:
	printf("%s%f\n","RAW Estimator Theta: ",E(p9_24_a,samples));
	printf("%s%f\n\n","RAW Estimator MSE: ",Var(p9_24_a,samples));
	
	//Part b:
	printf("%s%f\n","Antithetic Estimator Theta: ",E(p9_24_b,samples));
	printf("%s%f\n\n","Antithetic Estimator MSE: ",Var(p9_24_b,samples));
	
	//Part c:
	//Finding c_optimal:
	double X_mean = E(X_c,samples);
	mu = 10;

	srand(initial_seed);
	double sum = 0;
	struct s_answer answer;
	for(int i = 0; i < samples; i++){
		answer = p9_24_c();
		sum = sum + ((answer.X - X_mean)*(answer.Y - mu));
	}
	c = -(1.0)*((sum)/(samples - 1))/(Var(Y_c, samples));
	
	printf("%s%f\n","Control Variate Theta: ",E(CV_c,samples));
	printf("%s%f\n\n","Control Variate MSE: ",Var(CV_c,samples));
	
	//Part d:
	//Finding c_optimal:
	X_mean = E(X_d,samples);
	mu = 5.5;

	srand(initial_seed);
	sum = 0;
	for(int i = 0; i < samples; i++){
		answer = p9_24_d();
		sum = sum + ((answer.X - X_mean)*(answer.Y - mu));
	}
	c = -(1.0)*((sum)/(samples - 1))/(Var(Y_d, samples));
	
	printf("%s%f\n","Control Variate Theta: ",E(CV_d,samples));
	printf("%s%f\n\n","Control Variate MSE: ",Var(CV_d,samples));
	
}

/*
Output:
RAW Estimator Theta: 35.807855
RAW Estimator MSE: 355.870604

Antithetic Estimator Theta: 34.574959
Antithetic Estimator MSE: 155.902678

Control Variate Theta: 35.636518
Control Variate MSE: 96.009230

Control Variate Theta: 35.726939
Control Variate MSE: 77.691822
*/

/*
Discussion:
There were two main ways I had in mind to do antithetics, either seperate the arrival and departure U's, then have one be antithetic to the other,
or have every other entry in each list be antithetic. I guess you could also just not care and alternate between a new U and an antithetic 
regardless of what is occuring. This will probably also lower variance but be less effectve. I decided to go with alternating them so one 
arrival will be U, the next will be 1-U, and so on.

For c the mean of our control variates is just 10 Exponentials with lambda = 1, so it's 10*(1/lambda) = 10.

For d the mean of our control variate is 5.5 since 9*E[I] = 9*E[Exp(2)] = 9/2, so 10 - 9/2 = 5.5.
*/