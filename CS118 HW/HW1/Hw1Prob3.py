'''
Since immutable objects cannot be modified, when passed as the input a function a copy of the data is what is ultimately
passed to the function, but for mutable objects the address for the data is sent instead.

a) simple variable, while it has no protections against change, I think it's a reasonable choice
b) list, is able to contain multiple different objects and add further data
c) tuple, contains multiple objects, but also cannot change
'''