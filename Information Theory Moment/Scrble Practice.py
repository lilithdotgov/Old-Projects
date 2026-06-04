import os
import shutil
import random

os.chdir('C:/Users/15512/Desktop/Python Projects/Information Theory Moment/')

with open('Modified Word List.txt', 'r') as MWL:
    MWLTxt = MWL.read()
    MWLTxt = MWLTxt.split("\n")
    
    def Wordl():
        Wrdl = MWLTxt[random.randrange(0,2000,1)]
        for x in range(0,6,1):
            guess = input("Guess A Word!" + "\n")
            bull = 0
            close = 0
            i = 0
            while i<4:
                if guess[i] == Wrdl[i]:
                    bull = bull + 1
                elif guess[i] in Wrdl:
                    close = close + 1
                i = i + 1
            if bull == 4:
                return print("Success! Your Word Was:", Wrdl,"Your Guess was",guess)
            print(guess,"\n","Total Bullseye:",bull,"\n","Total Close:",close)
            print("Guesses Remaining:",5 - x)
        print("Better Luck Next Time! Your Word Was:",Wrdl)
    
    for i in range(0,20,1):
        Wordl()
        print("Wanna Play Again?")
    

    