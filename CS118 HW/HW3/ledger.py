from time import time
from hashlib import sha256

class Block:
    def __init__(self, data, prev_hash, new_hash):
        self.timestamp = time()
        self.data = data
        self.prev_hash = prev_hash
        self.new_hash = new_hash
        
        
class Blockchain:
    def __init__(self):
        self.head = b'Null'
        self.blocks = [] #Stores our blocks
        
        #Create an initial head with None as the data to avoid checking this edge case everytime we call add_block().
        #The actual performance gain here is probably neglibible since the CPU will just do branch prediction like crazy
        #but still, it *feels* like bad practice. Plus we don't require the user to make their own tail which could be a mess
        data = 'this is the head!'
        new_hash = sha256(bytes(data,'utf-8') + self.head).digest()
        self.blocks.append(Block(data, self.head, new_hash))
        self.head = new_hash
        
    def add_block(self, data):
        new_hash = sha256(bytes(data,'utf-8') + self.head).digest()
        self.blocks.append(Block(data, self.head, new_hash))
        self.head = new_hash
        
    def validate_chain(self):
        cur_head = b'Null' #Keeps track of hashes
        for block in self.blocks:
            if block.prev_hash == cur_head: #Past hash matches the prior block's expected hash
                cur_head = sha256(bytes(block.data,'utf-8') + cur_head).digest() #recalculate what the new hash should be
                print(f'Valid Block with data "{block.data}" and hash "{block.new_hash}"\n')
            else:
                print(f'Invalid Block with data "{block.data}" and hash "{block.new_hash}"\n')
                return False
                
        return True
        
print(f'Let us test our datatype by creating a new Blockchain, adding 4 blocks of data, and validating the chain\n')
print("-"*100,'\n')
chain = Blockchain()
chain.add_block("data1")
chain.add_block("data2")
chain.add_block("data3")
chain.add_block("data4")
print(f'{chain.validate_chain()}\n')
print("-"*100,'\n')
print(f'Now let us replace the second block with a fake block:\n')
print("-"*100,'\n')
temp = chain.blocks[1]
chain.blocks[1] = Block("fake data", b'fake prior hash', b'fake new hash')
print(f'{chain.validate_chain()}\n')
print("-"*100,'\n')
print("As expected, we catch the change! But what if we only change the data and keep the other hashes?")
print("-"*100,'\n')
chain.blocks[1] = Block("fake data",temp.prev_hash, temp.new_hash)
print(f'{chain.validate_chain()}\n')
print("-"*100,'\n')
print("We catch the change but incorrectly assert that the 3rd block is the invalid one!")
print("The correct way to catch this requires more finesse since there are a few different ways to insert false blocks")
print("However, that is outside the scope of the assignment, and as it stands we correctly identify the chain is invalid!")