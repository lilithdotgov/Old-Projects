#I had not realized I could use built-in functions. The constraint of the assignment
#made it seem like you should use loops to calculate min/max/avg
def Stocks(quarter):
    high = 0 
    low = 2**32
    avg = 0
    bull_start = 0
    bull_end = 0
    bull_length = 1
    for i in range(0,len(quarter)):
        if (quarter[i] > high):
            high = quarter[i]
        if (quarter[i] < low):
            low = quarter[i]
        avg = avg + quarter[i]
        if (i > 0): #covers edge case
            if (quarter[i] >= quarter[i-1]): #run continues
                bull_length = bull_length + 1
            else: #run ends with price drop
                if ((bull_end - bull_start) < bull_length): #new run is longer
                    bull_end = i; bull_start = bull_end - bull_length
                    bull_length = 1 #reset bull_length
                else: #new run is shorter
                    bull_length = 1 #reset bull_length
                    
    if ((bull_end - bull_start) < bull_length): #covers edge case of best run being at the end
        bull_end = len(quarter); bull_start = bull_end - bull_length 
    else:
        bull_start = bull_start + 1
    
    avg = avg/len(quarter)
    
    print(f'high =\t', high)
    print(f'low =\t', low)
    print(f'average =', avg)
    print(f'longest bull run = day ', bull_start, " to day ", bull_end)

stock_example = [ 150.0, 152.5, 153.0, 151.0, 151.0, 154.0, 158.0, 160.0, 159.0, 161.0, 165.0, 164.0, 163.0, 162.0, 162.5, 164.0, 166.0, 168.0, 170.0, 169.0, 168.0, 167.0, 166.0, 166.0, 167.0, 169.0, 171.0, 172.0, 173.0, 175.0, 174.0, 172.0, 170.0, 171.0, 172.0, 171.0, 170.0, 168.0, 169.0, 170.0, 172.0, 174.0, 175.0, 176.0, 177.0, 175.0, 174.0, 173.0, 171.0, 170.0, 168.0, 169.0, 171.0, 173.0, 174.0, 176.0, 178.0, 180.0, 182.0, 181.0, 179.0, 178.0, 177.0, 175.0, 174.0, 172.0 ]    
Stocks(stock_example) #Example