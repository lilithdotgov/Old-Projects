//Problem 2:
#include "stochastics.h"

double check(){
	double a = Exponential(2); 
	double b = Exponential(2); 
	double c = Exponential(2); 
	
	if (a == fmin(fmin(a,b),c)){return fmin(b,c);}
	else if (b == fmin(fmin(a,b),c)){return fmin(a,c);}
	else{return fmin(a,b);}
}


double p5_15(){
	double a = Exponential(2); 
	double b = Exponential(2); 
	double c = Exponential(2); 
	double d = Exponential(2); 
	double e = Exponential(2); 
	return fmin(fmin(fmin(fmin(a,b),c),d),e);
}

double p5_19(){
	double a = Exponential(2); 
	double b = Exponential(3); 

	if (a < b){return 100*exp(-5*a);}
	else{return 0;}
}

int main(){
	samples = 1000000;
	printf("%f\n",E(check, samples));
}
