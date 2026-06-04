from random import random
from math import exp

def f(x):
    return exp(exp(x))

def MonteCarlo(func,samples):
    sum = 0
    for i in range(0,samples):
        sum = sum + func(random())
        
    return sum / samples
        
print(MonteCarlo(f,9999999))