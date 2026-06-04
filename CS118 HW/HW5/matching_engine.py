import heapq
import math
import csv
import os

path = os.path.dirname(os.path.realpath(__file__))
os.chdir(path)

with open('l5_limit_orders.csv', newline='') as csv_trades: #Get our trades
    trades_reader = csv.reader(csv_trades)
    BuyHeap = []
    SellHeap = []
    heapq.heapify_max([BuyHeap])
    heapq.heapify([SellHeap])
    for row in trades_reader:
        if row[1] == "ASK":
            heapq.heappush_max(BuyHeap,(float(row[3]),int(row[4])))
        elif row[1] == "BID":
            heapq.heappush(SellHeap,(float(row[3]),int(row[4])))   

def match(BuyHeap,SellHeap):
    while BuyHeap[0][0] >= SellHeap[0][0]:
        if BuyHeap[0][1] > SellHeap[0][1]:
            print(f'{SellHeap[0][1]} Stocks traded at a spread of {BuyHeap[0][0]-SellHeap[0][0]}')
            BuyHeap[0] = (BuyHeap[0][0],BuyHeap[0][1] - heapq.heappop(SellHeap)[1])
        elif BuyHeap[0][1] < SellHeap[0][1]:
            print(f'{BuyHeap[0][1]} Stocks traded at a spread of {BuyHeap[0][0]-SellHeap[0][0]}')
            SellHeap[0] = (SellHeap[0][0],SellHeap[0][1] - heapq.heappop_max(BuyHeap)[1])
        elif BuyHeap[0][1] == SellHeap[0][1]: 
            print(f'{SellHeap[0][1]} Stocks traded at a spread of {BuyHeap[0][0]-SellHeap[0][0]}')
            heapq.heappop_max(BuyHeap)
            heapq.heappop(SellHeap)

test1 = [34, 1,2,14,4,23485,34]
test2 = [(1,34), (2,1),(17,2),(2,14),(13,4),(2,23485),(45463576,34)]

heapq.heapify(test2)

def print_heap(heap): #Used for testing
    i = 0
    for h in heap:
        print(f'{h}\t',end='')
        
        i += 1
        if int(math.log2(i+1)) == math.log2(i+1):
            print()

