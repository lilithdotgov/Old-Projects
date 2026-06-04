#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int initial_seed = 307;
int samples = 100000;

double U(double min_val, double max_val) //Gives a random double between max_val to min_val
{
	double u = (max_val - min_val)*(((float)rand())/RAND_MAX) + min_val;
	while ((u == min_val) || (u == max_val)){
		u = (max_val - min_val)*(((float)rand())/RAND_MAX) + min_val;
	}
	
	return u;
}

double E(int (*f)(void), double samples) //Gives the Expected Value of a given Random Variable
{
	double sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + (*f)();
	}
	
	return (double)sum/samples;
}

double Var(int (*f)(void), double samples) //Gives the Variance of a given Random Variable
{
	int sum = 0;
	for(int i = 0; i < samples; i++){
		sum = sum + pow((double)(*f)(),2.0);
	}
	
	return sum/samples - pow(E(f,samples),2.0);
}

void Permute(int *array, int length) //Permutes an array of elements
{
	for(int i = length - 1; i >= 1; i--){
		int P = (i + 1)*U(0,1);
		int temp = array[P];
		array[P] = array[i];
		array[i] = temp;
	}
}

double Time(int (*f)(void), int samples) // Gives the average execution time of a function
{
	clock_t begin = clock();
	for(int i =  0; i < samples; i++){
		(*f)();
	}
	clock_t end = clock();
	return (double)(end - begin) / CLOCKS_PER_SEC;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hits() //Simulates the random variable described in problem 2
{
	int cards = 100;
	int deck[cards];
	for(int i = 1; i <= cards; i++){
		deck[i - 1] = i;
	}
	
	int hits = 0;
	Permute(deck, cards);
	for(int i2 = 1; i2 <= cards; i2++){
		if (deck[i2 - 1] == i2){
			hits++;
		}
	}

	return hits;
}

int Contestants() //Simulates the random variable described in problem 3
{
	int players = 100;
	int temp_players = players;
	double elimination = 0.2;
	int rounds = 0;
	while (players > 0){
		for(int i = 0; i < players; i++){ //Simulates one round
			if (U(0,1) < elimination){
				temp_players--;
			}
		}
		players = temp_players;
		rounds++;
	}
	
	return rounds;
}

int Bernoulli() //Simulates the 25 Bernoulli random variable for problem 6 using an efficient-ish algorithm
{
	int samples = 25;
	int sum = 0;
	for(int i = 0; i < samples; i++){
		double rv = 5*U(0,1)-3;
		sum = sum + !((int)(abs(rv)+rv)/2); //This is a crazy hack I came up with, it may be more efficient in certain circumstances?
	}
	
	return sum;
}

int Bernoulli2() //Implements the "correct" algorithm for simulating successive independent Bernoullis efficently
{
	int samples = 25;
	double p = 0.2;
	int N = 0;
	int X = 0;
	while (samples > 0){
		N = (int)(log(U(0,1))/log(1-p))+1;
		if (samples - N >= 0){ //Checks if we still have more samples to take
			X = X + N - 1; //Adds all but one, since the last sample was a failure. Also works for edge case of getting exactly 25 samples
		}
		else{ //Occurs when we take more samples than 25
			X = X + samples; //Adds only the number of samples that were left before the current batch
		}
		samples = samples - N;
	}
	
	return X;
	
}

int Bernoulli3() //Same as Bernoulli2 but counts the number of U we generated for the 25 trials
{
	int samples = 25;
	double p = 0.2;
	int N = 0;
	int X = 0;
	int NU = 0; //Numher of U's generated
	while (samples > 0){
		N = (int)(log(U(0,1))/log(1-p))+1;
		NU++;
		if (samples - N >= 0){ //Checks if we still have more samples to take
			X = X + N - 1; //Adds all but one, since the last sample was a failure. Also works for edge case of getting exactly 25 samples
		}
		else{ //Occurs when we take more samples than 25
			X = X + samples; //Adds only the number of samples that were left before the current batch
		}
		samples = samples - N;
	}
	
	return NU;
	
}

int Dice() //Simulates the Random Variable of Problem 7
{
	int die[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int rolls = 0;
	while ((die[0] + die[1] + die[2] + die[3] + die[4] + die[5] + die[6] + die[7] + die[8] + die[9] + die[10]) > 0){ //This is awful
		int rv = (int)(6*U(0,1)) + (int)(6*U(0,1));
		die[rv] = 0;
		rolls++;
	}
	
	return rolls;
}

int Alternating() //Simulates the Random Variable of Problem 15
{
	double p1 = 0.55;
	if (U(0,1) < p1){
		int rv = 5*U(0,1);
		return 2*rv + 5;
	}
	else{
		int rv = 5*U(0,1);
		return 2*rv + 6;
	}
}

int main()
{
	printf("%s%f\n", "Mean of Problem 2: ", E(&Hits, samples));
	printf("%s%f\n\n", "Variance of Problem 2: ", Var(&Hits, samples));
	
	printf("%s%f\n\n", "Mean of Problem 3: ", E(&Contestants, samples));
	
	printf("%s\n\n", "I decided to see if I could improve upon the algorithm given in the book for Problem 6, lets see if my method even work!");
	printf("%s%f\n", "Mean of Bernoulli with Unorthodox Method: ", E(&Bernoulli, samples));
	printf("%s%f\n", "Mean of Bernoulli with Standard Method: ", E(&Bernoulli2, samples));
	printf("%s\n\n", "With the same mean it is clear that both methods are (hopefully) equivalent, but which is faster?");
	
	printf("%s%f\n", "Unorthodox Method Average Speed for 25 Bernoulli trials: ", Time(&Bernoulli, samples));
	printf("%s%f\n", "Standard Method Average Speed for 25 Bernoulli trials: ", Time(&Bernoulli2, samples));
	printf("%s\n\n", "Welp, I thought I was being clever with not needing any if statements and just directly computing a Bernoulli.");
	
	printf("%s%f\n\n", "Mean of Problem 6: ", E(&Bernoulli3, samples));
	
	printf("%s%f\n\n", "Mean of Problem 7: ", E(&Dice, samples));
	
	printf("%s\n\t", "Sequence of X values for problem 15: ");
	for(int i = 0; i < 200; i++){
		printf("%d%s", Alternating(), " ");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* OUTPUT:
Mean of Problem 2: 1.001120
Variance of Problem 2: 1.013618

Mean of Problem 3: 23.743310

I decided to see if I could improve upon the algorithm given in the book for Problem 6, lets see if my method even work!

Mean of Bernoulli with Unorthodox Method: 20.001410
Mean of Bernoulli with Standard Method: 19.996630
With the same mean it is clear that both methods are (hopefully) equivalent, but which is faster?

Unorthodox Method Average Speed for 25 Bernoulli trials: 0.032000
Standard Method Average Speed for 25 Bernoulli trials: 0.018000
Welp, I thought I was being clever with not needing any if statements and just directly computing a Bernoulli.

Mean of Problem 6: 5.798880

Mean of Problem 7: 61.275430

Sequence of X values for problem 15:
    10 14 9 8 7 13 7 12 11 11 9 13 10 9 5 13 9 11 13 12 11 12 6 6 8 10 12 7 6 9 6 5 12 14 14 11 5 13 5 14 13 14 10 9 10 13 10 7 13 11 7 8 9 
	10 10 7 5 7 13 13 11 6 7 9 14 5 6 14 5 7 13 12 8 14 11 9 13 12 10 9 7 14 12 8 13 13 5 5 9 9 5 7 5 13 6 7 13 5 5 12 5 5 9 10 7 11 6 12 10 
	5 7 11 9 10 13 8 14 11 9 5 11 13 11 11 8 11 13 9 11 13 7 11 8 13 10 5 8 5 14 5 9 12 8 9 11 7 13 12 11 6 13 13 8 10 8 13 14 8 9 7 5 13 9 
	11 7 9 13 6 6 9 9 7 5 11 13 5 13 8 9 14 8 11 6 6 13 7 6 11 14 14 6 10 13 14 7 8 8 9 13 11
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Answers for Questions with Written Responses:

Problem 1:

The algorithm is as follows:
1> GENERATE U(0,1)
2> IF U < 0.35, THEN X = 3
3> ELIF U < 0.65, THEN X = 1, STOP
4> ElIF U < 0.85, THEN X = 2, STOP
5> ELSE X = 3, STOP

Problem 13:

Let pois(i) = exp(-l)*(l^i)/(i!).
Poisson has a nice recursive relationship, where pois(i+1) = (l/(i+1))*pois(i).

We could pre-compute the denominator and then divide the numerator to ensure our pmf actually sums to 1, or, we can just discard any U(0,1) that
causes us to go past the kth poisson term, the distribution will be the same. This causes more U(0,1) to be generated, but saves on a computation
step that would occur every single time we need a random variable. If Lambda is not too large, the pmf decays quite quickly and so we shouldn't 
need to generate many extra U(0,1). 
The only issue now is that either we do a comparison every time U < P is true to check if our i is outside the bounds of 0 to k, or we 
accept i values outside our range. The latter is not so bad, since we can just do one final pass after generating our needed number of poisson
random variables to remove all X > k from out data.
.
The alternative method is to just use the inverse transform. Precompute the values for each pois(i),
order X in terms of greatest probability, then loop an if statement. We can't do our discard trick here again, since we would try to access 
elements outside the list of pre-computated values. We could add an if statement to check if X > k and discard it, but this would run every
loop WITHIN the loop, which is far FAR worse than just a multiplication being done once for every random variable.

Since we have that nice recursive relationship, we can turn sum(pois(i)) into pois(0)*sum((l/i)^i), indexed from 0 to k.
With this, we generate/scale to get a U between 0 and the sum.

Method 1 Algorithm:
1> GENERATE U(0,1)
2> i = 0, p = exp(-l), P = p
3> IF U < P, THEN X = i, STOP
4> p = (l*p)/(i + 1), P = P + p, i = i + 1
5> GOTO Line 3
...
end> DISCARD ALL X > k

Method 2 Algorithm:
0.1> CREATE List from 0 to k, i = 0, LET Element 0 of List = [pois(0), 0] //[] indicates a vector element
0.2> i = i + 1
0.3> LET Element i of List = [(Element i - 1 of List)*(l/i), i]
0.4> IF i <= k, GOTO Line 0.2
0.4> SORT List in descending order of the First Vector Entry
//This series of pre-computation steps should occur once when asking for a series of poissons

1> GENERATE U(0,1)*pois(0)*sum((l/i)^i), p = 0, i = 0
2> p = p + First Vector Entry of Element i of List
3> IF U < p, THEN X = Second Vector Entry of Element i of List, STOP
4> i = i + 1
5> GOTO Line 2
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* DISUCSSION: 
Well, I've tidied the code much better this time so it's more general but at a computational expense, but this isn't high-speed stock trading, it's
dumb to over-optimize this code. Still, I'm quite sad my little hack wasn't better for problem 6, but at least it wasn't THAT much slower.

Never did implement ACORN like I said I would, mainly because there doesn't seem to be a need. With integration having only 32000 values is
crippling, but with how these random variables are calculated it's not so bad. Still may do it some future day, but right now I don't have the
time sadly.

I have no clue how to compute the exact analytic value for problem 2. I cheated and googled the answer, felt like an idiot, then got even more
confused, then felt like an even bigger idiot, then got INCREDIBLY confused as to the variance. I no longer feel like an idiot, unless there is
a very elegant way to show the variance is 1 that I'm just not seeing. At least an Expected value of 1 is reasonable (kinda, I still think 
that linearity of the Expected value holding for dependent variables is black magic).
*/