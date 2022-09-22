def solution(sentences):
    tempRes = {}
    for j in range(len(sentences[0])):
        map = {}
        for i in range(len(sentences)):
            map[sentences[i][j]] = map.get(sentences[i][j], 0) + 1
        arr = sorted(map.items(), key=lambda x: -x[1])
        
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


# test case 1
case1 = [["your", "bear", "drinks", "beer"], ["your", "bear", "eats", "beer"], ["the", "bear", "drinks", "beer"]]

# test case 2
case2 = [["your", "bear", "drinks", "beer"], ["your", "bear", "eats", "beer"], ["the", "bear", "drinks", "beer"], ["your", "bear", "the", "beer"]]
print(solution(case1))