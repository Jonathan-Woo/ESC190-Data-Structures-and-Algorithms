# Lab 6

#
# We'll define a node of a binary tree and introduce some features of Python
# classes along the way
import random

class BST:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def insert(self, value):
        '''
        node.insert(5) is the same as BST.insert(node, 5)
        We use this when recursively calling, e.g. self.left.insert
        '''
        if value < self.value:
            if self.left == None:
                self.left = BST(value)
            else:
                self.left.insert(value)
        else:
            if self.right == None:
                self.right = BST(value)
            else:
                self.right.insert(value)

    def __repr__(self):
        '''The string representation of a node.
        Here, we convert the value of the node to a string and make that
        the representation.
        We can now use
        a = Node(4)
        print(a) # prints 4
        '''
        return str(self.value)

a = BST(4)
a.insert(2)
a.insert(5)
a.insert(10)
a.insert(3)
a.insert(15)

# Problem 1
# Draw (manually) the binary tree rooted in a.

          #    4
          #  /   \
          # 2     5
          #  \     \
          #   3     10
          #           \
          #           15

# Problem 2
# Write code to find the height of a Binary Search Tree

def height(node):
    if node == None:
        return 0
    else :
        # Compute the height of each subtree
        left_height = height(node.left)
        right_height = height(node.right)

        #Use the larger one
        if left_height > right_height :
            return left_height+1
        else:
            return right_height+1

# Problem 3

# Write code to print out the nodes of the BST using
# Breadth-First Search. How would you get the Breadth-First Traversal
# from the tree you've drawn?
# (Modify the BFS function from lecture for this problem)


def BFS_tree(node):
    h = height(node)
    for i in range(1, h + 1):
        BFS_tree_level(node, i)

def BFS_tree_level(node, level):
    if node == None:
        return
    if level == 1:
        print(node.value, end= " ")
    elif level > 1 :
        BFS_tree_level(node.left, level-1)
        BFS_tree_level(node.right, level-1)

# Problem 4

# Empirically investigate the relationship between the number of nodes in the
# tree and the height of the tree when inserting nodes with values generated
# using random.random()
def make_random_tree(n_nodes):
    '''Make a tree with n_nodes nodes by inserting nodes with values
    drawn using random.random()
    '''
    bst_tree = BST(random.random())
    for i in range(n_nodes - 1):
        bst_tree.insert(random.random())

    return bst_tree

def height_random_tree(n_nodes):
    '''Generate a random tree with n_nodes nodes, and return its height'''
    bst_tree = make_random_tree(n_nodes)
    return height(bst_tree)

def make_data(max_nodes):
    '''Make two lists representing the empirical relationship between
    the number of nodes in a random tree and the height of the tree.
    Generate N_TREES = 40 trees with each of
    n_nodes = 5, int(1.2*5), int(1.2^2*5), .....

    return n (a list of values of n_nodes) and h (a list of heights)
    '''
    N_TREES = 40
    n_nodes = 5
    n = []
    h = []
    i = 0

    while(1.2**i*5 <= max_nodes):
        for e in range(40):
            n.append(1.2**i*5)
            h.append(height_random_tree((int)(1.2**i*5)))
        i+=1

    return n, h

n, h = make_data(10000)
import matplotlib.pyplot as plt
plt.scatter(n, h)
plt.show()
plt.savefig("trees.png") #can save the data to disk