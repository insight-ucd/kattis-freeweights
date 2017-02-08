#!/usr/bin/env python

def is_paired(row):
    """
        Check if the dumbells on a row are paired
        The basic check is iterating through the row in pairs
        and checking if successive elements are the same
    """
    size = len(row)
    if size == 0:
        return True
    
    if size == 1:
        return False

    if size % 2 != 0:
        return False
    
    for i in range(0, size, 2):
        if(row[i] != row[i+1]):
            return False

    return True

def check_max_weight(row_1, row_2, M):
    """
        Here, we filter the rows by removing all weights less than or equal to M
        We check the filtered rows for pairings.
    """
    filt = lambda x: x > M
    row_1 = list(filter(filt, row_1))
    row_2 = list(filter(filt, row_2))
    return is_paired(row_1) and is_paired(row_2) 
    
def main():
    # read the rows of integers
    n = int(input())
    row_1 = list(map(int, input().strip().split()))
    row_2 = list(map(int, input().strip().split()))
    
    # create a list of unique weight values
    unique_weights = set()
    for w in row_1: 
        unique_weights.add(w)
    for w in row_2:
        unique_weights.add(w)
        
    # its more convenient for the set to be a list
    unique_weights = sorted(unique_weights)

    # if the dumbbells are already sorted there is nothing to do...
    if check_max_weight(row_1, row_2, 0):
        print('0')
        return
                    
    # this is the binary search through all possible values for the weights,
    # remove all weights less than or equal to M, if the rows are paired, then try
    # moving to a smaller weight...
    lo, hi = 0, len(unique_weights)

    while lo < hi:
        mid = (hi + lo) // 2
        M = unique_weights[mid]
        if check_max_weight(row_1, row_2, M): # check a lower weight
            hi = mid
        else:
            lo = mid + 1

    print(unique_weights[lo])
    return

if __name__ == '__main__':
    main()