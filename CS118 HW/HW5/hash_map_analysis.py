import heapq
import csv
import os
import time

path = os.path.dirname(os.path.realpath(__file__))
os.chdir(path)

#I am once again wishing python had type declarations like C, this is a bit of a headache without them!

class Node: #Note, this implementation assumes a tuple and cares about first index! Modify if reusing code in future!!!
    def __init__(self, data, link = None):
        self.data = data
        self.link = link
        
    def Insert(self, data): #Default behaviour upon a duplicate entry is to replace with new data. Don't know if this is best implementation
        if (self.data[0] == data[0]): #Replace value
            self.data = data
        elif (self.link == None): #Insert at end
            self.link = Node(data)
            return True #Tells LinkedList that a novel collision occured
        else:
            return self.link.Insert(data)
            
    def Search(self, data): #Assumes a string is passed
        if (self.data[0] == data): #This is main deviation, as it accesses first element of tuple
            return self
        elif (self.link == None):
            return False
        else:
            return self.link.Search(data)
            

class LinkedList: #Note, this implementation often assumes a tuple and cares about first index! Modify if reusing code in future!!!
    def __init__(self, head = None):
        self.head = head
        self.collisions = 0 #Keeps track of many collisions have occured
    
    def Insert(self, data): #Needs tuple
        if (self.head == None):
            self.head = Node(data)
        else:
            if (self.head.Insert(data) == True):
                self.collisions += 1
            
    def Search(self, data): #Needs string. Returns the node itsef, this makes it worse for pure searches, but it makes the code tidier so whatever
        if (self.head == None):
            return False
        else:
            return self.head.Search(data)
            
    def Update(self, data): #Needs to be fed a tuple!
        node = self.Search(data[0]) #This is main deviation, as it accesses first element of tuple
        if ((node != None) or (node != False)):
            node.data = data
        else:
            print("Item not in List")

class CustomHashMap:
    def __init__(self):
        self.size = 250
        self.HashTable = [] #It would be more efficient to be a numpy array, but whatever!
        
        for i in range(0,self.size): #Creates linked list for each of the 100 entries
            self.HashTable.append(LinkedList())
    
    def Hash(self, key):
        sum = 0
        i = 1
        for char in key:
            sum += (47**i)*ord(char)
            i += 1
        return sum % self.size   
        
    def BadHash(self, key): #Bad implementation for homework
        sum = 0
        i = 1
        for char in key:
            sum += ord(char)
            i += 1
        return sum % self.size   
    
    def Insert(self, data): #Assumes tuple
        hash = self.Hash(data[0])
        self.HashTable[hash].Insert(data)
        
    def BadHashInsert(self, data): #Uses bad hash
        hash = self.BadHash(data[0])
        self.HashTable[hash].Insert(data)
        
    def Search(self, data): #Assumes string
        hash = self.Hash(data)
        return self.HashTable[hash].Search(data)   


with open('l4_ticker_feed.csv', newline='') as csv_trades: #Get our stocks
    stocks_reader = csv.reader(csv_trades)
    
    PriceTableDict = dict()
    #Test Speed of Insertion
    start = time.time()
    for row in stocks_reader:
        PriceTableDict[row[0]] = row[1]   
    end = time.time()
    print(f'Dictionary Insertion time for all elements:\t{(1000*(end-start)):.3f}ms\n')
    csv_trades.seek(0)
    
    PriceTableHashMap = CustomHashMap()
    #Test Speed of Insertion
    start = time.time()
    for row in stocks_reader:
        PriceTableHashMap.Insert((row[0],row[1]))   
    end = time.time()
    print(f'CustomHashMap Insertion time for all elements:\t{(1000*(end-start)):.3f}ms\n')
    csv_trades.seek(0)
    
    #Test Speed of Searching
    start = time.time()
    for row in stocks_reader:
        PriceTableDict[row[0]] #We don't use "is" here to be fair to our implementation which returns the node when searched. This way the dict also returns its entry   
    end = time.time()
    print(f'Dictionary Search time for all elements:\t{(1000*(end-start)):.3f}ms\n')
    csv_trades.seek(0)
    
    #Test Speed of Searching
    start = time.time()
    for row in stocks_reader:
        PriceTableHashMap.Search(row[0])   
    end = time.time()
    print(f'CustomHashMap Search time for all elements:\t{(1000*(end-start)):.3f}ms\n')
    csv_trades.seek(0)
    
    #Now to compare collisions between the Hashes
    PriceTableBadHashMap = CustomHashMap()
    for row in stocks_reader:
        PriceTableBadHashMap.BadHashInsert((row[0],row[1]))
    
    sum = 0
    for LL in PriceTableHashMap.HashTable:
        sum += LL.collisions
    print(f'CustomHashMap # of novel collisions:\t\t{sum}\n')
    
    sum = 0
    for LL in PriceTableBadHashMap.HashTable:
        sum += LL.collisions
    print(f'Bad CustomHashMap # of novel collisions:\t{sum}\n')
    
msg = f'''{"-"*120}
This is about what I would expect given we have only 5^3 unique values in the data set, and the Bad Hash
itself only maps those values into 13 buckets. Since the first insert in a bucket is not a collision,
that leaves us with 5^3 - 13 = 112 collisions which is what we got!

It's also interesting to see that my highly unoptimized HashMaps are only ~2x worse than python's built-in methods,
usually I expect the difference to be order(s) of magnitude!

Overall this one was a very fun problem to do! Sorry it's submitted late, I was quite busy!
'''

print(msg)