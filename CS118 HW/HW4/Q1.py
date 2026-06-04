from collections import deque
import math

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
        
    def BFT(self): #This implementation varies from Q5 so that it can output it as specified for Q1. Notably it is less elegant!
        queue = deque()
        
        #Base case for root node:
        queue.append(self.root)
        
        def get_height(node):
            if not node:
                return 0
            return 1 + max(get_height(node.left), get_height(node.right))
        height = get_height(self.root) 
        
        i = 0
        while queue and (math.log2(i+1) < height):
            node = queue.popleft()
            i += 1
            
            if (node == None):
                print("NULL ",end='')
                
                queue.append(None)
                queue.append(None)
            else:
                print(f'{node.data} ',end='')
                
                queue.append(node.left)
                queue.append(node.right)
                
            if int(math.log2(i+1)) == math.log2(i+1):
                print()   
   
def ConstructTree(inorder, preorder):
    def ConstructTree_(inorder, preorder):
        root = None
        if inorder:
            root = TreeNode(preorder[0])
            index = inorder.index(preorder[0])

            root.left = ConstructTree_(inorder[:index], preorder[1:index+1])
            root.right = ConstructTree_(inorder[index+1:], preorder[index+1:])
        
        return root
        
    BinaryTree(ConstructTree_(inorder, preorder)).BFT()
    
ConstructTree(input().split(" "), input().split(" "))