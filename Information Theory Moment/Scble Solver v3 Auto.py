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
    #temp = SetW.copy()
    
    TrySet = {-1:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0}
 
    for Words in range (0,2023,10):
        Wrdl = MWLTxt[Words]
        print(Wrdl)
        for tries in range(0,10,1):
            
            if tries != 0:
                WordWeight = {}
                for word in MWLTxt:
                    if word in WordWeight:
                        WordWeight[word] = 0
                    else:
                        WordWeight[word] = 0
                TotalWords = len(SetW)
                print(TotalWords)
                for EWord in MWLTxt:
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
                            p = (TotalWords - Removed) / TotalWords
                            try:
                                Entropy = -1 * p * numpy.log2(p)
                            except Warning:
                                Entropy = 0
                            WordWeight[EWord] = WordWeight[EWord] + Entropy
                            
            #print(sorted(WordWeight.items(), key=lambda item: item[1]))    
            if tries == 0:
                guess = "sate"
            elif len(SetW) == 1:
                guess = SetW[0]
            elif len(SetW) == 2:
                guess = SetW[0]
            else:
                EList = sorted(WordWeight.items(), key=lambda item: item[1])
                
                guess = EList[-1][0]
            #print("guess:",guess)
            if len(SetW) < 10 and EList[-1][1] < 1.5:
                guess = SetW[0]
            
            bull = 0
            close = 0
            i = 0
            while i<4:
                if guess[i] == Wrdl[i]:
                    bull = bull + 1
                elif guess[i] in Wrdl:
                    close = close + 1
                i = i + 1
            if bull == 4 and not (tries == 9):
                #print("Success! Tries for",Wrdl,":", tries)
                if (tries + 1) in TrySet:
                    TrySet[(tries + 1)] = TrySet[(tries + 1)] + 1
                else:
                    TrySet[(tries + 1)] = 1
                
            x = guess + " " + str(bull) + ":" + str(close) 
            if bull == 4:
                x = "Restart"
            if tries == 9:
                x = "Restart"
                if -1 in TrySet:
                    TrySet[-1] = TrySet[-1] + 1
                else:
                    TrySet[-1] = 1
                print("    " + Wrdl)

            if "Restart" in x:
                SetW = MWLTxt.copy()
                MaybeSetW = []
                break
            elif ":" in x:
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

    print(TrySet)