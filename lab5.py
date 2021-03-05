import numpy as np
import heapq

class Node:
    def __init__(self, name):
        self.name = name
        self.connections = []
        self.visited = False

    def __lt__(self, node2):
        return True


def connect(node1, node2, weight):
    node1.connections.append({"node": node2, "weight": weight})
    node2.connections.append({"node": node1, "weight": weight})


def BFS(node):
    q = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        print(cur.name)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True


################################################################################

def get_all_nodes(node):
    '''Return a list of the nodes in the graph of nodes connected to node
    (N.B., the nodes can be indirectly connected as well)'''

################################################################################

def unvisit_all(node):
    '''Change all n.visited to False in all the nodes in the graph of nodes
    connected to node. Use BFS to find all the nodes'''



###############################################################################

def DFS_rec(node):
    '''Print out the names of all nodes connected to node using a
    recursive version of DFS'''
    # The Algorithm
    # Pick any node. If it is unvisited, mark it as visited and recur on all its adjacent nodes.
    # Repeat until all the nodes are visited, or the node to be searched is found.

    q = [node]
    # First, check if the current node is unvisited - if yes, it is appended in the visited set
    for con in cur.connections:
        if not con["node"].visited:
            print(cur.name)
            q.append(con["node"])
            # Then for each neighbor of the current node, call DFS_rec for neighbor
            for neighbor in cur.connections:
                DFS_rec(neighbor)

    # base case: when all nodes are visited, the function then returns

################################################################################

def DFS_nonrec(node):
    '''Print out the names of all nodes connected to node using a non-recursive
    version of DFS. Make it so that the nodes are printed in the same order
    as in DFS_rec'''
    q = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop()
        print(cur.name)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True

################################################################################
#
# OPTIONAL
#

def dijsktra_slowish(node):
    '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
    need to use a priority queue'''
    S = [node]
    d = {node.name: 0}

    unexplored = get_all_nodes(node)
    unexplored.remove(node)

    while len(unexplored) > 0:
        # your code here
        pass

    return d

def dijkstra_pq(node):
    d = {}  # d[node.name] is the length of the shortest path from node to node_name
    pq = [(0, node)]  # the first thing that will be popped from pq
    while len(pq) > 0:  # keep adding nodes
        cur_dist, cur_node = heapq.heappop(pq)
        if cur_node.name in d:
            continue

        d[cur_node.name] = cur_dist
        for con in cur_node.connections:
            dist = con["weight"] + cur_dist
            node = con["node"]
            heapq.heappush(pq, (dist, node))

    return d


if __name__ == '__main__':
    TO = Node("TO")
    NYC = Node("NYC")
    DC = Node("DC")
    CDMX = Node("CDMX")
    SF = Node("SF")

    connect(TO, NYC, 3)
    connect(TO, SF, 6)
    connect(TO, CDMX, 7)
    connect(NYC, DC, 2)
    connect(SF, DC, 5)

    # L = get_all_nodes(TO)
    # DFS(TO)
    # #DFS_rec(TO)
    # unvisit_all(TO)
    # DFS(TO)
    # print(dijsktra_slowish(TO))