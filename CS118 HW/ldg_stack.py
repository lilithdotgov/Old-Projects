class StackEmpty(Exception):
    """Raised when an operation cannot be performed due to there being no elements in the stack"""
    def __str__(self):
        return "Stack is Empty, this operation cannot be performed"

class stack:
    def __init__(self):
        self.index = -1
        self.data = []
    
    def push(self, datum):
        self.data.append(datum)
        self.index += 1
        
    def empty(self):
        self.index = -1
        self.data = []
        
    def pop(self):
        if self.index < 0:
            raise StackEmpty
        else:
            del self.data[self.index]
            self.index -= 1
            
    def top(self):
        if self.index < 0:
            raise StackEmpty
        else:
            return self.data[self.index]
            