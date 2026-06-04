'''
1) I would say Encapsulation is the process of combining multiple pieces of data and functionalities into one object with
a few set functions that it can perform when called by the user. Rather than manually bitbanging an I2C message, the protocal
and all its components can be formed into one object which the user can call with their given message and the object does all 
the actual work under the hood. Information Hiding, on the other hand, is used in Encapsulation to abstract multiple complex
bits of data into something more simple for the user (an array of points in C vs. a list in Python) by hiding what occurs under the hood.
However, it's a more general technique that I would attribute to tasks other than Encapsulation, as it can be used to ensure data
integrity from change, or to create some level of privacy when it comes to attempting to access said data.

2) The Logical View would suggest that a dictionary is a continous array of a key followed by it's value followed by the next key
and so on, since that's how a real dictionary is written on paper. The Physical View would be that it's inefficient to store the keys
and values together, since keys are fixed in storage size but the values are not, and so changing any of the values would now
require moving all of the other keys and values to make room or remove it. I'd bet that Python stores an array of keys which are
all pointers to the piece of memory that was allocated for its corresponding value, which can be anywhere in RAM and so it being modified
is less of a concern (and since you don't assign memory in anything less than multiple chunks of kilobytes, you might not need to change
where the value is located either if there's still more space in the allocation).

For some reason the autograder expects an explanation involving recursion and base cases and terminationdespite the quesiton not being 
about either!!! Hopefully adding this extra line resolves the issue!
'''