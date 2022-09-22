#!/bin/python3

import math
import os
import random
import re
import sys
from typing import List


def find_mistakes(submissions: List[List[str]]) -> List[str]:
    """Find all mistakes from the input submissions list. A correct word 
    is a word that occurs most often in each spot across all submissions. If 
    two words are occur equally often in the top spot, both are considered
    'correct'. A mistake is any word that is not a correct word. The returned 
    list of mistakes should be sorted by most occurrences to least occurrences 
    with ties broken alphabetically.
    """
    tempRes = {}
    for j in range(len(submissions[0])):
        dic = {}
        for i in range(len(submissions)):
            dic[submissions[i][j]] = dic.get(submissions[i][j], 0) + 1
        arr = sorted(dic.items(), key=lambda x: -x[1])
        
        k = 0
        first_freq = -1
        
        for tup in arr:
            if k == 0:
                first_freq = tup[1]
            else:
                if tup[1] < first_freq:
                    tempRes[tup[0]] = tempRes.get(tup[0], 0) + tup[1]
            k += 1
            
    res = []
    for name, _ in sorted(tempRes.items(), key=lambda x: (-x[1], x[0])):
        res.append(name)
    return res
        
    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    submissions_rows = int(input().strip())
    submissions_columns = int(input().strip())

    submissions = []

    for _ in range(submissions_rows):
        submissions.append(input().rstrip().split())

    result = find_mistakes(submissions)

    fptr.write('\n'.join(result))
    fptr.write('\n')

    fptr.close()
