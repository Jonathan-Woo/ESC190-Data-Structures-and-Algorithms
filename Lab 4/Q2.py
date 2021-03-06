'''
2. In Python, write a function find(L, e) that takes in a sorted list L and an element e, and returns the lowest index in L such that L[i] == e. (-1 if there is no such index)
   Write a function that takes in a sorted linst L and an element e, and returns the index of the highest index in L such that L[i] == e. (-1 if there is no such index).
   The function should run in O(log(n)) time.
   This should help you with Project 1.
'''
def find(L, e):
    head = 0
    tail = len(L) - 1
    mid = 0

    while tail - head >= 1:
        #get to the middle of the list
        mid = head + ((tail - head)//2)

        #keep track of the head and tail of the list
        #solution when they converge

        if L[mid] >= e:
            tail = mid
        elif L[mid] < e:
            head = mid

    if L[mid] == e:
        return mid
    else:
        return -1

def highest(L, e):
    head = 0
    tail = len(L)
    mid = 0

    while tail - head >= 1:
        #get to the middle of the list
        mid = head + ((tail - head + 1)//2)

        #keep track of the head and tail of the list
        #solution when they converge

        if L[mid] > e:
            tail = mid
        elif L[mid] <= e:
            head = mid

    if L[mid] == e:
        return mid
    else:
        return -1

if __name__ == "__main__":
    L = [1,1,1,1,1,1,1];

    print(find(L,1))
    # print(highest(L,1))

# [0 1 2 3 4 5]
# [0 1 2] [3 4 5]
#
# [0] [1 2]
#
# [0 1] [2]
