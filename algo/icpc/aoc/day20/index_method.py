import time, sys

start=time.time()

def sol(part, file):
    if part == "part1":
        numbers = [int(x) for x in open(file)]
        epoch = 1
        
    elif part == "part2":
        numbers = [int(x) * 811589153 for x in open(file)]
        epoch = 10

    indices = list(range(len(numbers)))
    sz = len(indices)

    for _ in range(epoch):
        for i in range(len(indices)):
            indices.pop(j := indices.index(i))
            print("=== doing i", i)
            print("inserting to", (j+numbers[i]) % (sz-1))
            indices.insert((j+numbers[i]) % (sz-1), i)
            print([numbers[x] for x in indices])

    zero = indices.index(numbers.index(0))

    first = numbers[indices[(zero + 1000) % len(numbers)]]
    second = numbers[indices[(zero + 2000) % len(numbers)]]
    third = numbers[indices[(zero + 3000) % len(numbers)]]
    print("sol", first, second, third, "sum", first + second + third)
    
sol("part1", "ex1.txt")

end=time.time()
print("running time", round(end-start,5))