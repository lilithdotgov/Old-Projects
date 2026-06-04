//Problem 2:
#include "stochastics.h"


double p2_a(){ //Random variable of interest
	return exp(pow(U(0,1),2.0));
}

double p2_b(){ //Again but with antithetical variates
	double rv = U(0,1);
	return (exp(pow(rv,2.0)) + exp(pow(1-rv,2.0)))/2.0;
}

struct s_answer{
	double X;
	double Y;
};

double c;
double mu;
//Mutable global variables are evil but I'm lazy

struct s_answer p2_c(){ //Again but with control variates
	double rv = U(0,1); double rv2 = U(0,1); double Y;
	if (rv < 0.75){
		Y = rv2;
	}
	else{
		Y = pow(rv2,1.0/3.0);
	}
	struct s_answer answer;
	answer.X = exp(pow(rv2,2.0));
	answer.Y = Y;
	
	return answer;
}

double X_c(){ //Our variable of interest of part d
	return p2_c().X;
}

double Y_c(){ //Control variable of part d
	return p2_c().Y;
}

double CV_c(){ //Uses the control variate to get X
	struct s_answer answer = p2_c();
	double X = answer.X; double Y = answer.Y;
	return X + c*(Y - mu);
}

double p2_d(){ //Again but with stratified sampling
	double sum = 0;
	for(int i = 0; i < 10; i++){
		sum = sum + exp(pow(U(i*0.1,0.1+(i*0.1)),2.0));
	}
	return sum/10.0;
}

double p2_e(){ //Again but with importance sampling
	double X; double rv = U(0,1);
	if (rv < 0.75){
		X = U(0,1);
	}
	else{
		X = pow(U(0,1),1.0/3.0);
	}
	
	return (exp(pow(X,2.0)))/((3.0/4.0)*(1+pow(X,2.0)));
}

int main(){
	//Part a:
	printf("%s\n","Part a:");
	for(int i = 2; i <= 6; i++){
		samples = pow(10.0,i);
		printf("%s%d%s%f\n","RAW Estimator Theta for N = 10^",i,": ",E(p2_a,samples));
		printf("%s%d%s%f\n\n","RAW Estimator MSE for N = 10^",i,": ",Var(p2_a,samples));
	}

	//Part b:
	printf("\n%s\n","Part b:");
	for(int i = 2; i <= 6; i++){
		samples = pow(10.0,i);
		printf("%s%d%s%f\n","Antithetic Theta for N = 10^",i,": ",E(p2_b,samples/2.0));
		printf("%s%d%s%f\n","Antithetic MSE for N = 10^",i,": ",Var(p2_b,samples/2.0));
		printf("%s%d%s%f\n\n","Antithetic (scaled by 2) for N = 10^",i,": ",2*Var(p2_b,samples/2.0));
	}
	
	//Part c;
	printf("\n%s\n","Part c:");
	for(int i = 2; i <= 6; i++){
		samples = pow(10.0,i);
		
		//Finding c_optimal:
		double X_mean = E(X_c,samples);
		mu = 9.0/16.0;

		srand(initial_seed);
		double sum = 0;
		struct s_answer answer;
		for(int i = 0; i < samples; i++){
			answer = p2_c();
			sum = sum + ((answer.X - X_mean)*(answer.Y - mu));
		}
		c = -(1.0)*((sum)/(samples - 1))/(Var(Y_c, samples));

		printf("%s%d%s%f\n","Control Variate Theta for N = 10^",i,": ",E(CV_c,samples));
		printf("%s%d%s%f\n\n","Control Variate MSE for N = 10^",i,": ",Var(CV_c,samples));
	}
	
	//Part d:
	printf("\n%s\n","Part d:");
	for(int i = 2; i <= 6; i++){
		samples = pow(10.0,i);
		printf("%s%d%s%f\n","Stratified Theta for N = 10^",i,": ",E(p2_d,samples/10.0));
		printf("%s%d%s%f\n","Stratified MSE for N = 10^",i,": ",Var(p2_d,samples/10.0));
		printf("%s%d%s%f\n\n","Stratified MSE (scaled by 10) for N = 10^",i,": ",Var(p2_d,samples/10.0));
	}
	
	//Part e:
	printf("\n%s\n","Part e:");
	for(int i = 2; i <= 6; i++){
		samples = pow(10.0,i);
		printf("%s%d%s%f\n","Stratified Theta for N = 10^",i,": ",E(p2_e,samples));
		printf("%s%d%s%f\n\n","Stratified MSE for N = 10^",i,": ",Var(p2_e,samples));
	}
}

/*
Output:
Part a:
RAW Estimator Theta for N = 10^2: 1.505427
RAW Estimator MSE for N = 10^2: 0.263233

RAW Estimator Theta for N = 10^3: 1.488255
RAW Estimator MSE for N = 10^3: 0.231340

RAW Estimator Theta for N = 10^4: 1.461634
RAW Estimator MSE for N = 10^4: 0.226346

RAW Estimator Theta for N = 10^5: 1.463389
RAW Estimator MSE for N = 10^5: 0.225910

RAW Estimator Theta for N = 10^6: 1.461916
RAW Estimator MSE for N = 10^6: 0.224647


Part b:
Antithetic Theta for N = 10^2: 1.477560
Antithetic MSE for N = 10^2: -0.006513
Antithetic (scaled by 2) for N = 10^2: -0.013026

Antithetic Theta for N = 10^3: 1.468771
Antithetic MSE for N = 10^3: 0.024992
Antithetic (scaled by 2) for N = 10^3: 0.049983

Antithetic Theta for N = 10^4: 1.461380
Antithetic MSE for N = 10^4: 0.027449
Antithetic (scaled by 2) for N = 10^4: 0.054897

Antithetic Theta for N = 10^5: 1.464453
Antithetic MSE for N = 10^5: 0.028180
Antithetic (scaled by 2) for N = 10^5: 0.056360

Antithetic Theta for N = 10^6: 1.462393
Antithetic MSE for N = 10^6: 0.027874
Antithetic (scaled by 2) for N = 10^6: 0.055748


Part c:
Control Variate Theta for N = 10^2: 1.445678
Control Variate MSE for N = 10^2: 0.059907

Control Variate Theta for N = 10^3: 1.457958
Control Variate MSE for N = 10^3: 0.068230

Control Variate Theta for N = 10^4: 1.463697
Control Variate MSE for N = 10^4: 0.069622

Control Variate Theta for N = 10^5: 1.462323
Control Variate MSE for N = 10^5: 0.067948

Control Variate Theta for N = 10^6: 1.462485
Control Variate MSE for N = 10^6: 0.068150


Part d:
Stratified Theta for N = 10^2: 1.471215
Stratified MSE for N = 10^2: -0.266545
Stratified MSE (scaled by 10) for N = 10^2: -0.266545

Stratified Theta for N = 10^3: 1.464649
Stratified MSE for N = 10^3: -0.021504
Stratified MSE (scaled by 10) for N = 10^3: -0.021504

Stratified Theta for N = 10^4: 1.462105
Stratified MSE for N = 10^4: -0.001711
Stratified MSE (scaled by 10) for N = 10^4: -0.001711

Stratified Theta for N = 10^5: 1.462758
Stratified MSE for N = 10^5: 0.000208
Stratified MSE (scaled by 10) for N = 10^5: 0.000208

Stratified Theta for N = 10^6: 1.462592
Stratified MSE for N = 10^6: 0.000394
Stratified MSE (scaled by 10) for N = 10^6: 0.000394


Part e:
Stratified Theta for N = 10^2: 1.462855
Stratified MSE for N = 10^2: -0.001930

Stratified Theta for N = 10^3: 1.469913
Stratified MSE for N = 10^3: 0.018211

Stratified Theta for N = 10^4: 1.463908
Stratified MSE for N = 10^4: 0.020288

Stratified Theta for N = 10^5: 1.461765
Stratified MSE for N = 10^5: 0.019896

Stratified Theta for N = 10^6: 1.462635
Stratified MSE for N = 10^6: 0.019985
*/

/*
Discussion:
For part c my control variate of choice was (3/4)(1+x^2) since that's the first two terms of the taylor series of e^x^2. The mean of which
is (3/4)^2

For stratified sampling I just divided up the interval into 10 equal parts. Is this optimal? Probably not, but it's decent enough.

For part d I re-used the variate from part c, so it's (3/4)(1+x^2) again.
*/