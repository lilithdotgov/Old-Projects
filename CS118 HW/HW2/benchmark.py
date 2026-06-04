import csv
import os 
import numpy as np
import time

path = os.path.dirname(os.path.realpath(__file__))
os.chdir(path)
#Above code should hopefully make it so this script runs regardless of system and location

restricted_list = []
restricted_set = set()
restricted_array = np.array([])

with open('l1_restricted.csv', newline='') as csv_restricted: #Get our restricted values
    restricted_reader = csv.reader(csv_restricted)
    for row in restricted_reader:
        if row[0] == "symbol": #Kinda a hacky way to do this, but whatever
            continue
        restricted_list.append(row[0])
        restricted_set = restricted_set | {row[0]}
        restricted_array = np.append(restricted_array,row[0])
    
#Define our functions to check if trade is restricted or not
def is_restricted_list(symbol):
    if symbol in restricted_list:
        return True
    else:
        return False
        
def is_restricted_set(symbol):
    if symbol in restricted_set:
        return True
    else:
        return False
        
def is_restricted_array(symbol):
    if symbol in restricted_array:
        return True
    else:
        return False
    
#Get the trades and time each method
with open('l1_trades.csv', newline='') as csv_trades:
    trades_reader = csv.reader(csv_trades)
       
    time_start = time.time()
    for row in trades_reader:
        is_restricted_list(row[1])
    time_end = time.time()
    print("List total time:\t",time_end-time_start)
    print(f'List total money lost:\t${(time_end-time_start) * 1000 * 0.01}')
    csv_trades.seek(0)
  
    time_start = time.time()
    for row in trades_reader:
        is_restricted_set(row[1])
    time_end = time.time()
    print("Set total time:\t\t",time_end-time_start)
    print(f'Set total money lost:\t${(time_end-time_start) * 1000 * 0.01}')
    csv_trades.seek(0)
    
    time_start = time.time()
    for row in trades_reader:
        is_restricted_array(row[1])
    time_end = time.time()
    print("Array total time:\t",time_end-time_start)
    print(f'Array total money lost:\t${(time_end-time_start) * 1000 * 0.01}')
    csv_trades.seek(0)