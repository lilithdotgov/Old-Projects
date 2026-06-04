//Problem 8.7:

/*
Discussion:
The SD of the sample is roughly 3, and so to estimate E[X] with a SD of 0.1 from the true value of E[X] you'd need 
3/sqrt(n+16) < 0.1 => sqrt(n+16)/3 > 10 => sqrt(n+16) > 30 => n > 30^2 - 16 => n > 884 => around 885 more samples,
assuming that the true SD of the distribution of X is around 3. 
*/