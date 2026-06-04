from collections import deque

class TreeNode:
    def __init__(self, data, left = None, right = None):
        self.data = data
        self.left = left
        self.right = right
        
    def update_left(self,new_left):
        self.left = new_left
    
    def update_right(self,new_right):
        self.right = new_right
        
    def update_data(self,new_data):
        self.data = new_data

class BinaryTree:
    def __init__(self, root):
        self.root = root
        
    def BFT(self):
        queue = deque()
        
        #Base case for root node:
        queue.append(self.root)
    
        while queue:
            node = queue.popleft()
            print(f'{node.data}\t',end='')
            
            if (node.left != None): #Checks if left is node
                queue.append(node.left)
            if (node.right != None): #Checks if right is node
                queue.append(node.right)