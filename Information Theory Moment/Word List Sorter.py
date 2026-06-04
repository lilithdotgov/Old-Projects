import os
import shutil

os.chdir('C:/Users/15512/Desktop/Python Projects/Information Theory Moment/')

with open('Original Word List - Copy.txt', 'r') as OG, open('Modified Word List.txt', 'w') as MWL:
    
    MWLText = OG.read()
    MWLText = MWLText.lower()
    MWLText = MWLText.replace('\n',' ')
    MWLText = MWLText.split()

    TempTxt = MWLText.copy()
    for word in MWLText:
        WrdChck = []
        for letter in word:
            if letter not in WrdChck:
                WrdChck.append(letter)
            else:
                TempTxt.remove(word)
                break
    MWLText = TempTxt

    for word in MWLText:
        MWL.write(word + '\n')
    
    
