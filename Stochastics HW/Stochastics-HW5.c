#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + (*f)();
	}
	
	return (double)sum/samples;
}

double E_d(double (*f)(void), double samples){ //Gives the Expected Value of a given Random Variable
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + (*f)();
	}
	
	return (double)sum/samples;
}

double Var_i(int (*f)(void), double samples){ //Gives the Variance of a given Random Variable
	int sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + pow((double)(*f)(),2.0);
	}
	
	return sum/samples - pow(E(f,samples),2.0);
}

double Var_d(double (*f)(void), double samples){ //Gives the Variance of a given Random Variable
	int sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + pow((double)(*f)(),2.0);
	}
	
	return sum/samples - pow(E(f,samples),2.0);
}

void Permute(int *array, int length){ //Permutes an array of elements
	for(int i = length - 1; i >= 1; i--){
		int P = (i + 1)*U(0,1);
		int temp = array[P];
		array[P] = array[i];
		array[i] = temp;
	}
}

double Time_i(int (*f)(void), int samples){ // Gives the average execution time of a function
	clock_t begin = clock();
	for(int i =  0; i < samples; i++){
		(*f)();
	}
	clock_t end = clock();
	return (double)(end - begin) / CLOCKS_PER_SEC;
}

double Time_d(double (*f)(void), int samples){ // Gives the average execution time of a function
	clock_t begin = clock();
	for(int i =  0; i < samples; i++){
		(*f)();
	}
	clock_t end = clock();
	return (double)(end - begin) / CLOCKS_PER_SEC;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Composition(){ //Random Variable of Problem 4.16
	double rv = U(0,1);
	if (rv < 0.3){
		return (3*((int)U(0,2)) + 6); //Gives values of 6 or 9 equally likely
	}
	else if (rv < 0.6){
		return (((int)U(0,5)) + 1); //Gives values between 1 to 5 equally likely
	}
	else if (rv < 0.86){
		return (3*((int)U(0,2)) + 7); //Gives values of 7 or 10 equally likely
	}
	else{
			return 8;
	}
}

//This problem required me to skip it and try again after completing 5.7 and 5.8, very tricky!
int TwoGeometric(){
	double rv = U(0,1);
	if (rv < 0.5){
		return ((int)(log(U(0,1))/log(1.0/2.0))) + 1;
	}
	else{
		return ((int)(log(U(0,1))/log(2.0/3.0))) + 1;
	}
}

double LinearInv(){ //Random Variable of Problem 5.2
	double rv = U(0,1);
	if (rv > 0.25){
		return (-sqrt(12*(1-rv)) + 6);
	}
	else{
		return (2*sqrt(rv) + 2);
	}
}

double Weilbull(){ //Random Variable of Problem 5.4
	double a = 1;
	double b = 2;
	return pow((-1/a)*log(U(0,1)),1/b);
}

double ExponentialInv(){ //Random Variable of Problem 5.5
	return (2*((int)U(0,2))-1)*(1.0/2.0)*log(U(0,1)); //Skips the need for a comparison if we just change sign 50% of the time
}

double Problem8a(){ //We split it into the cdfs x, x^3, and x^5
	double rv = U(0,1);
	if (rv < 1.0/3.0){
		return U(0,1);
	}
	else if (rv < 2.0/3){
		return pow(U(0,1), 1.0/3.0);
	}
	else{
		return pow(U(0,1), 1.0/5.0);
	}
}

double Problem8b(){ //Neat trick in here to avoid an extra comparison!
	double rv = U(0,1);
	if (rv < 2.0/3){
		return U(0,1);
	}
	else{
		return (-1.0/2.0)*log(U(0,1));
	}
}

double Insurance(){ //Random Variable of Problem 5.10
	double p = 0.05; int n = 1000; double c = p/(1 - p); double pr = pow(1 - p, n); double F = pr;
	double rv = U(0,1);
	int i = 0;
	while (rv > F){ //Generates number of claims
		pr = pr*(c*(n - i)/(i + 1.0));
		F = F + pr;
		i++;
	}
	//Now we have generated the number of claims, next to find their costs
	double l = 1/800.0;
	double sum = 0;
	while (i > 0){ //Generates cost of each claim
		sum = sum + (-1/l)*log(U(0,1));
		i--;
	}

	if (sum < 50000){
		return 0;
	}
	else{
		return 1;
	}
}

int main()
{
	//srand(initial_seed);
	//printf("%s%f\n", "Mean of Problem 16: ", E(&Problem16, samples));

	srand(initial_seed);
	printf("%s\n\t", "Sequence of X values for problem 4.16: ");
	for(int i = 0; i < 200; i++){
		printf("%d%s", Composition(), " ");
	}
	
	srand(initial_seed);
	printf("\n\n%s%f\n\n", "Mean of Problem 4.16: ", E(&Composition, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s\n\t", "Sequence of X values for problem 4.17: ");
	for(int i = 0; i < 200; i++){
		printf("%d%s", TwoGeometric(), " ");
	}
	
	srand(initial_seed);
	printf("\n\n%s%f\n\n", "Mean of Problem 4.17: ", E(&TwoGeometric, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.2: ", E(&LinearInv, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.4: ", E(&Weilbull, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.5: ", E(&ExponentialInv, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n", "Mean of Problem 5.8.a: ", E(&Problem8a, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.8.b: ", E(&Problem8b, samples)); //Sanity check
	
	srand(initial_seed);
	printf("%s%f\n\n", "Mean of Problem 5.10: ", E(&Insurance, samples)); //Sanity check
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* OUTPUT:
Sequence of X values for problem 4.16:
        9 9 8 6 1 4 6 9 8 3 9 1 3 4 3 8 8 6 3 7 8 2 1 10 9 5 10 8 6 4 8 10 6 5 3 8 3 4 9 4 6 10 8 10 6 7 3 7 8 9 8 6 8 6 9 1 2 7 10 3 1 4 8 4 4 7
		8 6 1 4 8 10 7 2 4 4 8 9 7 4 2 8 3 5 2 6 9 6 1 9 4 8 6 8 9 10 5 3 8 6 8 4 9 9 5 9 6 1 7 9 6 7 1 1 5 7 7 10 8 5 6 2 7 1 6 5 10 8 6 9 8 9 7
		7 6 8 7 7 8 7 3 7 7 9 2 9 1 10 9 10 4 5 4 8 6 7 10 7 5 8 10 3 8 1 8 9 7 7 2 2 7 4 4 9 5 7 2 5 8 3 2 5 1 9 9 10 8 7 9 6 9 7 10 6 4 4 7 9 7
		8

Mean of Problem 4.16: 6.480655

Sequence of X values for problem 4.17:
        1 1 5 1 2 4 6 1 3 1 11 1 1 3 1 5 2 4 2 1 1 5 2 1 1 2 1 1 4 2 3 1 2 1 1 1 5 1 1 6 1 2 1 1 1 5 1 2 1 3 4 5 1 2 5 1 3 2 1 1 4 3 1 1 1 2 2 3
		1 1 5 1 2 2 2 2 5 2 12 2 6 2 1 2 5 2 3 3 1 2 3 5 5 2 10 4 1 1 3 9 1 2 1 2 1 1 1 1 1 3 3 7 6 2 1 1 4 4 1 1 2 4 3 1 1 1 10 2 5 3 1 4 1 4 2
		1 1 1 1 1 6 1 1 2 2 1 1 2 2 1 1 2 10 2 2 5 1 1 1 1 3 2 1 3 2 2 3 4 5 1 1 3 1 2 1 6 1 2 1 1 3 1 10 2 1 1 4 2 4 3 1 1 1 1 1 1 1 1 1 8

Mean of Problem 4.17: 2.499393

Mean of Problem 5.2: 3.665406

Mean of Problem 5.4: 0.886782

Mean of Problem 5.5: -0.000485

Mean of Problem 5.8.a: 0.694556
Mean of Problem 5.8.b: 0.500332

Mean of Problem 5.10: 0.106510
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Answers for Questions with Written Responses:
Problem 5.7:
In order to get F(X) from a sum of Fi(X) times a weight, pi, you generate a U, then pick an i depending on the pi values and your U.
With that i you generate another U, then calculate your X as U applied to the inverse of Fi.

Problem 5.8.c Algorithm:
1> LET p = {p1, p2, p3, ... pn-1, pn} indexed from 1 to n, i = 1, P = p{i}
2> GENERATE U1(0,1)
3> GENERATE U2(0,1)
4> IF U1 < P, X = U2^(1/i), STOP
5> ELSE i = i + 1, P = P + p{i}, GOTO LINE 4
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* DISCUSSION: 
Used your advice of re-initializing the seed! Also partially bloated my code by having different functions for integers and doubles when it comes
to expected value, variance, and timing. Doesn't seem like there's a better option in C so it is what it is.

4.17 Was very tricky first time around, needed to skip it and then came back after I realized how easy it was having finished 5.7 and 5.8! 

Not much more to say, I liked the last problem, it was fun to finally sink our teeth into a real-world problem!
*/