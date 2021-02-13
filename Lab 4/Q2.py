'''
2. In Python, write a function find(L, e) that takes in a sorted list L and an element e, and returns the lowest index in L such that L[i] == e. (-1 if there is no such index)
   Write a function that takes in a sorted linst L and an element e, and returns the index of the highest index in L such that L[i] == e. (-1 if there is no such index).
   The function should run in O(log(n)) time.
   This should help you with Project 1.
'''

def find(L, e):
    '''Takes a sorted list L and element e, returns the lowest
    index in L such that L[i] == e
    '''
    if e < L[0] or e > L[-1]:
        return -1

    half = len(L)//2 + 1
    if e == L[half]:
        return half
    elif e < L[half]:
        return find(L[:half],e)
    elif e > L[half]:
        return find(L[half:],e) + half


def highest(L, e):
    if e < L[0] or e > L[-1]:
        return -1

    half = len(L)//2
    if e == L[half]:
        return half
    elif e > L[half]:
        return find(L[half:],e) + half
    elif e < L[half]:
        return find(L[:half],e)


if __name__ == "__main__":
    L = [0,1,2,4,5,5,6];

    print(find(L,1))
    print(highest(L,1))

