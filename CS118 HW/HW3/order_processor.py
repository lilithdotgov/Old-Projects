from collections import deque
from random import random as U
import csv
import os

path = os.path.dirname(os.path.realpath(__file__))
os.chdir(path)
#Above code should hopefully make it so this script runs regardless of system and location

class TradeQueue:
    def __init__(self):
        self.queue = deque()
        self.history = deque()
        
    def add_order(self, data):
        if data[1] == "CANCEL": 
            self.undo_last(data) #Send data over to undo_last for removal
        else:
            self.queue.append(data)
            self.history.append(data)
        
    def undo_last(self, data):
        for entry in reversed(self.queue): #Faster if we search starting from the back of queue
            if (data[2] == entry[2]) and (data[4] == entry[4]) and (entry[1] != "CANCEL"):
                self.queue.remove(entry)
                self.history.append([data[0]] + ["CANCEL SUCCESS"] + data[2:])
                return
            
        self.history.append([data[0]] + ["CANCEL FAILURE"] + data[2:])
        
    def process_next(self):
        self.queue.popleft()


#Now, in order to simulate getting a ton of requests at once and processing them we can use some Stochastic processes knowledge
#in order to simulation this event. There are already timestamps for the requests, and let's say that we process requests at
#a uniform rate with mean 5. Now we simply generate the next time we finish processing a request and see which occurs first
def StochasticSim(trades, N): #N is our stopping condition, we don't take any more requests afterwards
    n = 1 #which request we are on
    t = 1000 #time
    t_process = float('inf') #time of next process to be done, we assign it to infinity for now since we haven't started yet
    t_request =  int(trades[n][0]) #time of next request
    TQ = TradeQueue()
    while True:
        if (t_request < t_process) and (n < 1000): #Request occurs next
            t = t_request
            TQ.add_order(trades[n])
            n += 1
            t_request = int(trades[n][0])
            
            if t_process == float('inf'): #We had nothing in need of processing prior
                t_process = t + 10*U()
                
        elif (n < 1000): #Processing happens next
            t = t_process
            
            if TQ.queue == deque([]): #Nothing left in queue, set next processing time to inf
                t_process = float('inf')
            else:
                TQ.process_next()
                t_process = t + 10*U()
                
        elif TQ.queue != deque([]): #Still some requests to handle
            TQ.process_next()
            
        else: #Nothing left to do, terminate program and print ActionHistory
            for entry in TQ.history:
                print(f"{entry}\n")
            return

with open('l3_orders.csv', newline='') as csv_trades: #Get our trades
    trades_reader = csv.reader(csv_trades)
    trades = []
    for row in trades_reader:
        trades.append(row)
        
    StochasticSim(trades, 1000)
    
#From the output we can see that we get a fair share of failures and successes to cancel an order.
#The mean time between requests is about 5.5, so with a mean processing time of 5, it makes sense that
#we typically process an item before it can be cancelled