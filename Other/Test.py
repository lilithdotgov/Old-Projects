import random

def Geo():
    j = 0
    p = 0.25
    while True:
        U = random.random()
        if U < 0.25:
            j = j + 1
        else:
            return j
            
N = 100000
s = [0] * 250

i = 0
while i < N:
    n = Geo()
    s[n] = s[n] + 1
    i = i + 1
    
i = 0
while i < 250:
    print(s[i]/N)
    i = i + 1