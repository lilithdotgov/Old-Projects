'''
1) A developer can simulate a do-while loop by having a boolean variable (bvar), setting it to True right before the loop,
then having the loop condition depend solely on bvar. Finally, within the loop, the last thing to be executed should be
to check if the condition of interest is still being met, if so continue as normal, else set bvar to false.

Ex:
bvar = True
while bvar:
    ...
    
    if (...):
        pass
    else:
        bvar = False


2) The following code:

for next_int in range(1, MAX_VAL + 1):
    if next_int % 2 == 0:
        sum_val += next_int
    else:
        prod_val *= next_int

can be turned into:

i = 1
while (i < MAX_VAL + 1):
    if i % 2 == 0:
        sum_val += i
    else:
        prod_val *= i 
    i += 1
'''