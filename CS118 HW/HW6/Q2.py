from random import randint
import heapq

def RanArray(N): #We allow for duplicate entries to ensure algorithms can handle such edge cases
    arr = []
    for i in range(0,N):
        arr.append(randint(0,N)) #Range of intergers is arbitrary, but let's ensure they're no greater than the length of the array
        
    return arr

def SelectionSort(array):
    comparisons = 0
    exchanges = 0
    
    arr = array.copy() #Ensures we don't modify original array
    for i in range(0,len(arr)-1):
        min = (arr[i],i)
        for i2 in range(i,len(arr)):
            comparisons += 1
            if (arr[i2] < min[0]):
                min = (arr[i2],i2)
        arr[i], arr[min[1]] = arr[min[1]], arr[i]
        exchanges += 1
        
    print(f'Exchanges = {exchanges}\t Comparisons = {comparisons}')
    return arr
    
def BubbleSort(array):
    comparisons = 0
    exchanges = 0
    
    arr = array.copy() #Ensures we don't modify original array
    swaps = None
    while (swaps != 0):
        swaps = 0
        for i in range(0,len(arr)-1):
            comparisons += 1
            if (arr[i] > arr[i+1]):
                exchanges += 1
                arr[i], arr[i+1] = arr[i+1], arr[i]
                swaps += 1
    
    print(f'Exchanges = {exchanges}\t Comparisons = {comparisons}')    
    return arr
    
def InsertionSort(array):
    comparisons = 0
    exchanges = 0
    
    arr = array.copy() #Ensures we don't modify original array
    for i in range(1,len(arr)):
        cur = i
        while (cur > 0) and (arr[cur] < arr[cur-1]):
            exchanges += 1
            comparisons += 1
            arr[cur], arr[cur-1] = arr[cur-1], arr[cur]
            cur -= 1
        
    print(f'Exchanges = {exchanges}\t Comparisons = {comparisons}')    
    return arr
    
def Merge(array1, array2): #Assumes input array already in order! Also tracks comparisons
    comparisons = 0
    
    arr = []
    while (array1) and (array2):
        comparisons += 1
        if (array1[0] <= array2[0]):
            arr.append(array1[0])
            del array1[0]
        else:
            arr.append(array2[0])
            del array2[0]
    if (not array1) and (array2): #Puts remaining array2 entries at end
        arr = arr + array2
    elif (array1) and (not array2): #Puts remaining array1 entries at end
        arr = arr + array1
        
    return (arr, comparisons)
    

def MergeSort(array):
    comparisons = 0
    arr = array.copy() #Ensures we don't modify original array
    left_arr = arr[0:(len(arr)//2)]
    right_arr = arr[(len(arr)//2):]
    if (len(arr) > 1):
        left_arr, left_comparisons = MergeSort(left_arr)
        right_arr, right_comparisons = MergeSort(right_arr)
        comparisons += left_comparisons + right_comparisons
        
    merged_arr, merge_comparisons = Merge(left_arr,right_arr)
    comparisons += merge_comparisons
    return (merged_arr, comparisons)
    
class MaxHeap: #Specific for the problem, has added code to track comparisons
    def __init__(self):
        self.arr = []
        self.comparisons = 0
        self.exchanges = 0
        
    def insert(self,data):
        self.arr.append(data)
        child = len(self.arr)-1
        parent = (child-1)//2
        while (parent > -1) and (self.arr[parent] < self.arr[child]):
            self.comparisons += 1
            self.exchanges += 1
            
            self.arr[parent], self.arr[child] = self.arr[child], self.arr[parent]
            child = parent
            parent = (child-1)//2
            
    def pop(self):
        if not self.arr: #Checks if empty
            return None
        
        self.arr[0], self.arr[len(self.arr)-1] = self.arr[len(self.arr)-1], self.arr[0]
        pop = self.arr.pop()
        
        parent = 0
        l_child = 2*parent+1
        r_child = 2*parent+2
        while ((2*parent+1 <= len(self.arr)-1) and (self.arr[parent] < self.arr[l_child])) or ((2*parent+2 <= len(self.arr)-1) and (self.arr[parent]) < self.arr[r_child]):
            self.comparisons += 3 #2 to check if parent is smaller, 1 to check which child is bigger
            self.exchanges += 1
            
            if ((2*parent+2 <= len(self.arr)-1) and (self.arr[l_child] < self.arr[r_child])):
                self.arr[parent], self.arr[r_child] = self.arr[r_child], self.arr[parent]
                parent = r_child
                l_child = 2*parent+1
                r_child = 2*parent+2
            else:
                self.arr[parent], self.arr[l_child] = self.arr[l_child], self.arr[parent]
                parent = l_child
                l_child = 2*parent+1
                r_child = 2*parent+2
            
        return pop

def HeapSort(array):
    arr = array.copy() #Ensures we don't modify original array
    heap = MaxHeap()
    for i in arr:
        heap.insert(i)
        
    for i in range(1,len(arr)+1):
        arr[-i] = heap.pop()
        
    print(f'Exchanges = {heap.exchanges}\t Comparisons = {heap.comparisons}')
    return arr

array = RanArray(999) #Chose to do 999 instead of 1000 just to ensure algorithms handle parity edge-cases

#Check if the arry was properly sorted
print("Did the algorithms correctly sort the array? And with what computation cost?")
print("Selection Sort:")
print(f'Selection Sort is Correct = {SelectionSort(array) == sorted(array)}\n')
print("Bubble Sort:")
print(f'Bubble Sort is Correct = {BubbleSort(array) == sorted(array)}\n')
print("Insertion Sort:")
print(f'Insertion Sort is Correct = {InsertionSort(array) == sorted(array)}\n')
print("Merge Sort:")
merge_sort_result = MergeSort(array) #This kinda sucks but oh well
print(f'Exchanges = n/a\t Comparisons = {merge_sort_result[1]}') 
print(f'Merge Sort is Correct = {merge_sort_result[0] == sorted(array)}\n')
print("Heap Sort:")
print(f'Heap Sort is Correct = {HeapSort(array) == sorted(array)}\n')