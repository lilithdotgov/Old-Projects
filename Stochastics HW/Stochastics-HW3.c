#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int initial_seed = 307;

double U(double min_val, double max_val) //Gives a random double between max_val to min_val
{
	double u = (max_val - min_val)*(((float)rand())/RAND_MAX) + min_val;
	while ((u == min_val) || (u == max_val)){
		u = (max_val - min_val)*(((float)rand())/RAND_MAX) + min_val;
	}
	return u;
}

double f1(double x) //Problem 5 function
{
	return exp(x+(x*x));
}

double f2(double x) //Problem 7 function
{
	return exp(-(x*x));
}

double f3(double x, double y) //Problem 9 function
{
	return exp(-(x + y));
}

double f4a(double x) //Problem 10 function 
{
	return x*exp(x);
}

double f4b(double x) //Problem 10 function 
{
	return x;
}

double f4c(double x) //Problem 10 function 
{
	return exp(x);
}

double MonteCarlo(double (*f)(double), int samples, double min_val, double max_val) //1-Dimensional Monte Carlo Integrator
{
	double sum = 0;
	double rv = 0;
	if (!((min_val == -INFINITY) && (max_val == INFINITY))){ //Executes with normal bounds from min_val to max_val
		for(int i = 0; i < samples; i++){
			sum = sum + (*f)(U(min_val, max_val));
		}
		
		sum = ((max_val - min_val)*sum) / samples;
	}
	
	else if ((min_val == -INFINITY) && (max_val == INFINITY)){ //Executes with -inf to inf bounds
		for(int i = 0; i < samples; i++){
			rv = U(0,1);
			sum = sum + ((*f)(log((1/rv)-1)))/(rv-(rv*rv));
		}
		
		sum = sum/samples;
	}
	else{ //Not needed for assignment, may add support for min_val to inf or -inf to max_val bounds
		;
	}
	
	return sum;
}

double MonteCarloFail(double (*f)(double, double), int samples) //It is a "failure" for reasons explained in the discussion
{
	double sum = 0;
	double rvx = 0;
	double rvy = 0;
	for(int i = 0; i < samples; i++){
		rvx = U(0,1);
		rvy = U(0,1);
		if (rvy < rvx){
			sum = sum + ((*f)((1/rvx)-1,(1/rvy)-1))/(rvx*rvx*rvy*rvy);
		}
	}
	return sum / samples;
}

double Trapezoidal(double (*f)(double), int samples, double min_val, double max_val) //Trapezoidal Rule for Integration
{
	double sum = 0;
	double dx = (max_val - min_val)/samples;
	for(int i = 0; i < samples; i++){
		sum = sum + (f(min_val + i*dx) + f(min_val + (i + 1)*dx))*(dx/2);
	}
	return sum;
}

double Nmin(int samples) //Problem 12 function N
{
	int total = 0;
	for(int i = 0; i < samples; i++){
		double sum = 0;
		while (sum < 1){
			sum = sum + U(0,1);
			total++;
		}
	}
	return (float)total/samples;
}

double Nmax(int samples) //Problem 13 function N
{
	int total = 0;
	for(int i = 0; i < samples; i++){
		double sum = 1;
		while (sum > exp(-3)){
			sum = sum*U(0,1);
			total++;
		}
	}
	return (float)total/samples;
}

double PNmax(int samples, int val) //Problem 13 function P(N = i)
{
	int success = 0;
	for(int i = 0; i < samples; i++){
		int total = 0;
		double sum = 1;
		while (sum > exp(-3)){
			sum = sum*U(0,1);
			total++;
		}
		if (total == val){
			success++;
		}
	}
	return (float)success/samples;
}

int main()
{
	
	srand(initial_seed);
	printf("%s%f\n", "Problem 5 Monte Carlo:\t ", MonteCarlo(&f1, 32000, -2.0, 2.0));
	printf("%s%f\n\n", "Problem 5 Trapezoidal:\t ",Trapezoidal(&f1, 32000, -2.0, 2.0));
	
	printf("%s%f\n", "Problem 7 Monte Carlo:\t ", MonteCarlo(&f2, 32000, -INFINITY, INFINITY));
	printf("%s%f\n\n", "Known Value: sqrt(pi) =\t ", 1.77245);
	
	printf("%s%f\n", "Problem 9 Monte Carlo:\t ", MonteCarloFail(&f3, 32000));
	printf("%s%f\n\n", "Known Value: 1/2 =\t ", 1.0/2);
	
	printf("%s%f\n", "Problem 10 Monte Carlo:\t ", MonteCarlo(&f4a, 32000, 0, 1) - MonteCarlo(&f4b, 32000, 0, 1)*MonteCarlo(&f4c, 32000, 0, 1));
	printf("%s%f\n\n", "Known Value: (3-e)/2 =\t ", (3-exp(1))/2);
	
	printf("%s%f\n", "Problem 12 with 10^2 Samples:\t ", Nmin(100));
	printf("%s%f\n", "Problem 12 with 10^3 Samples:\t ", Nmin(1000));
	printf("%s%f\n", "Problem 12 with 10^4 Samples:\t ", Nmin(10000));
	printf("%s%f\n", "Problem 12 with 10^7 Samples:\t ", Nmin(10000000));
	printf("%s%s\n\n", "Personal Guess for the Value:\t ","e");
	
	printf("%s%f\n", "Problem 13a with 10^2 Samples:\t ", Nmax(100));
	printf("%s%f\n", "Problem 13a with 10^3 Samples:\t ", Nmax(1000));
	printf("%s%f\n", "Problem 13a with 10^4 Samples:\t ", Nmax(10000));
	printf("%s%f\n", "Problem 13a with 10^7 Samples:\t ", Nmax(10000000));
	printf("%s%s\n\n", "Personal Guess for the Value:\t ","4");
	
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 0):\t ", PNmax(10000, 0));
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 1):\t ", PNmax(10000, 1));
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 2):\t ", PNmax(10000, 2));
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 3):\t ", PNmax(10000, 3));
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 4):\t ", PNmax(10000, 4));
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 5):\t ", PNmax(10000, 5));
	printf("%s%f\n", "Problem 13b with 10^4 Samples for P(N = 6):\t ", PNmax(10000, 6));
}

/*	Discussion:
	I mentioned that there was a reason for me having named one of the functions "MonteCarloFail", and it's due
	to my inability to figure out the right balance between generalizability and efficiency with my code. You 
	should have seen that I decided to make U have inputs for a range of values rather than just 0 to 1. This
	is a nice generalization of the function and with minimal loss of efficiency. I then struggled for a while
	trying to hit a similar balance when it came to integrating with infinite bounds, ultimately gave up
	trying to find an elegant solution, and made a seperate function just to solely deal with problem 9. I also
	didn't bother adding multi-dimensionality or integration bounds from a real number to +-inf as part of the 
	MonteCarlo function, which I had considered doing so at the beggining. Turns out, making an elegant and 
	highly versatile library is hard! 
	
	I'd decided to use the logistic function for my integration between +-inf, as it seemed more efficient than
	arctan which was my second choice in mind.
	
	One thing of note is that the C standard library rand() function SUCKS. It has only ~32000 values and
	with seemingly no way to increase that max. I believe this is what led to some pretty bad errors on some
	of the integrals, as 32000 samples weren't enough to converge to more than 1-3 decimals, but any more samples
	would be useless as it'd just loop back on the PRNG. Next assignment I plan to implement a better PRNG
	function. My current thoughts go to ACORN, simply because it is an underutilized but very robust PRNG. It
	also has a funny name to me...
	
	Otherwise, I don't think there's anything worth note in my code, I don't think it's hyper-optimized, but it
	should be atleast not too unoptimized. I'm still very inexperienced with C and so there's likely boundless
	Improvements that could be made with greater experience. 
	
	I'm going to work out the analytical solution for 13a and 13b if I can because they were quite surprising 
	(I'm guessing it's something to do with convolutions and the CLT?). Fun Problems! */