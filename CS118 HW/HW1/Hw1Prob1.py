import string

def Q1(sentence):
    if (type(sentence) != str):
        print("Invalid input")
        return
    
    words = sentence.strip(string.punctuation + " ")
    for char in string.punctuation:
        words = words.replace(char, "")
    n_words = len(words.split())
    
    char_set = set()
    for char in words.lower().replace(" ",""):
        char_set = char_set.union(char)
    n_unique_char = len(char_set)
    
    max_length = 0
    for word in words.split():
        max_length = max(max_length, len(word))
        
    max_vowels = 0
    for word in words.split():
        max_vowels = max(max_vowels, word.count("a") + word.count("e") + word.count("i") + word.count("o") + word.count("u"))
        
    print(f'{n_words} {n_unique_char} {max_length} {max_vowels}')
    
Q1(input())