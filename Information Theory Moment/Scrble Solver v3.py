import os
import shutil
import random
import numpy
import warnings

warnings.filterwarnings('error')
numpy.seterr(all='warn')

os.chdir('C:/Users/15512/Desktop/Python Projects/Information Theory Moment/')

with open('Modified Word List.txt', 'r') as MWL:
    MWLTxt = MWL.read()
    MWLTxt = MWLTxt.split("\n")
    MWLTxt.remove("")
    SetW = MWLTxt.copy()
    temp = SetW.copy()
    firstGuess = True
    
    
    while True:
        if firstGuess != True:
            WordWeight = {}
            for word in MWLTxt:
                if word in WordWeight:
                    WordWeight[word] = 0
                else:
                    WordWeight[word] = 0
            
            for EWord in MWLTxt:
                temp = SetW.copy()
                for b in range(0,5,1):
                    for c in range(0,5,1):
                        Removed = 0
                        if b + c > 4:
                            continue
                        for word in SetW:
                            match = 0
                            placeMatch = 0
                            for i in range(0,4):
                                if EWord[i] in word: 
                                    match = match + 1
                                if EWord[i] == word[i]:
                                    placeMatch = placeMatch + 1
                            if not ((placeMatch == b) and (match == b + c)):
                                Removed = Removed + 1
                        p = (len(temp) - Removed) / len(temp)
                        try:
                            Entropy = -1 * p * numpy.log2(p)
                        except Warning:
                            Entropy = 0
                        WordWeight[EWord] = WordWeight[EWord] + Entropy
                        
            print(sorted(WordWeight.items(), key=lambda item: item[1])) 
            if len(SetW) < 50:
                print(SetW)
            
        x = input("Enter Command: Restart | word b:c (Updates Sets) \n")
        if "Restart" in x:
            SetW = MWLTxt.copy()
            MaybeSetW = []
            firstGuess = True
        elif ":" in x:
            firstGuess = False
            b = int(x[5])
            c = int(x[7])
            temp = SetW.copy()
            
            for word in temp:
                match = 0
                placeMatch = 0
                for i in range(0,4):
                    if x[i] in word: 
                        match = match + 1
                    if x[i] == word[i]:
                        placeMatch = placeMatch + 1
                if not ((placeMatch == b) and (match == b + c)):
                    SetW.remove(word)