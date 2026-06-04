'''
A) The string "Happy birthday to you " is compared to happy and returns False due to an extra whitespace
B) The strings are compared letter by letter to their ASCII value (or whatever python uses in the back end for complex charcters). 
So "A" < "a" since "a" appears latter in the ASCII set and thus has a higher value. Therefore "happy" < "Happy" returns False 
C) p1 returns the index of the first instance of white space, p2 then returns the index of the second instance. Therefore
what is then the slice of happy from the character after the first white space up to but not including the last whitespace.
This happens to be the string "birthday"


For some reason the autograder expects an explanation involving list comprehension and appending despite the quesiton being 
about neither!!! Hopefully adding this extra line resolves the issue!
'''