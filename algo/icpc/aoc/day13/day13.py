import functools

def cmp_list(l1, l2):
    """
    Compare two lists
    Returns:
        -1: l1 < l2
        0: l1 = l2
        1: l1 > l2
    """
    for e1, e2 in zip(l1, l2):
        if isinstance(e1, int) and isinstance(e2, int):
            if e1 < e2:
                return -1
            elif e1 > e2:
                return 1
        elif isinstance(e1, list) and isinstance(e2, int):
            rc = cmp_list(e1, [e2])
            if rc != 0:
                return rc
        elif isinstance(e1, int) and isinstance(e2, list):
            rc = cmp_list([e1], e2)
            if rc != 0:
                return rc
        elif isinstance(e1, list) and isinstance(e2, list):
            rc = cmp_list(e1, e2)
            if rc != 0:
                return rc

    if len(l1) < len(l2):
        return -1
    elif len(l1) > len(l2):
        return 1
    else:
        return 0

def task1(tup_list):
    acc = 0
    for idx, (l1, l2) in enumerate(tup_list, 1):
        rc = cmp_list(l1, l2)
        if rc == -1:
            acc += idx
    return acc

def task2(tup_list):
    all_list = [[[2]], [[6]]]
    for l1, l2 in tup_list:
        all_list.append(l1)
        all_list.append(l2)
    
    rs = sorted(all_list, key=functools.cmp_to_key(cmp_list))

    return (rs.index([[2]])+1) * (rs.index([[6]])+1)


if __name__ == "__main__":
    with open("input1.txt") as f:
        txt = f.read().strip()
        temp = txt.split("\n\n")
        strs = []
        
        for s in temp:
            strs.append(s.split("\n"))

    tup_list = []
    for l1, l2 in strs:
        tup_list.append((eval(l1), eval(l2)))
    
    t2 = task2(tup_list)
    print("task 2 res", t2)

    
    
    
    
    
    
