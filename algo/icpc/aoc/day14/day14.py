def print_matrix(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end='')
        print("")

def grid1(strs, min_x, max_x, max_y):
    width = max_x - min_x
    height = max_y
    matrix = [['.' for j in range(width+1)] for i in range(height+1)]

    for l in strs:
        coord = [str.split(",") for str in l]
        prev_x = int(coord[0][0]) 
        prev_y = int(coord[0][1]) 
        for i in range(len(coord)-1):
            x = int(coord[i+1][0])
            y = int(coord[i+1][1])
            if x == prev_x:
                if y > prev_y:
                    while prev_y <= y:
                        matrix[prev_y][prev_x-min_x] = '#'
                        prev_y += 1
                else:
                    while prev_y >= y:
                        matrix[prev_y][prev_x-min_x] = '#'
                        prev_y -= 1
            if y == prev_y:
                if x > prev_x:
                    while prev_x <= x:
                        matrix[prev_y][prev_x-min_x] = '#'
                        prev_x += 1
                else:
                    while prev_x >= x:
                        matrix[prev_y][prev_x-min_x] = '#'
                        prev_x -= 1
            
            prev_x = x
            prev_y = y
    
    return matrix


def grid2(strs, min_x, max_x, max_y):
    width = 1000
    height = max_y
    matrix = [['.' for j in range(width+1)] for i in range(height+1)]

    for l in strs:
        coord = [str.split(",") for str in l]
        prev_x = int(coord[0][0]) 
        prev_y = int(coord[0][1]) 
        for i in range(len(coord)-1):
            x = int(coord[i+1][0])
            y = int(coord[i+1][1])
            if x == prev_x:
                if y > prev_y:
                    while prev_y <= y:
                        matrix[prev_y][prev_x] = '#'
                        prev_y += 1
                else:
                    while prev_y >= y:
                        matrix[prev_y][prev_x] = '#'
                        prev_y -= 1
            if y == prev_y:
                if x > prev_x:
                    while prev_x <= x:
                        matrix[prev_y][prev_x] = '#'
                        prev_x += 1
                else:
                    while prev_x >= x:
                        matrix[prev_y][prev_x] = '#'
                        prev_x -= 1
            
            prev_x = x
            prev_y = y

    matrix.append(["."] * len(matrix[0]))
    matrix.append(["#"] * len(matrix[0]))
    return matrix

def fall1(matrix, yy, xx):
    if xx < 0 or xx >= len(matrix[0]):
        return -1

    y = yy
    while matrix[y][xx] == ".": 
        y += 1
        if y > len(matrix) - 1:
            return -1
    
    
    if matrix[y][xx-1] == ".":
        return fall1(matrix, y, xx-1)
    elif matrix[y][xx+1] == '.':
        return fall1(matrix, y, xx+1)
    else:
        matrix[y-1][xx] = "o"
        # print_matrix(matrix)
        return 0

def part1(matrix):
    for i in range(100000):
        rc = fall1(matrix, 0, 500 - min_x)
        if rc == -1:
            print("part 1 ans", i)
            break


def fall2(matrix, yy, xx):
    if xx < 0 or xx >= len(matrix[0]):
        print("x out of bound, should not happen")
        return -1

    y = yy
    while matrix[y][xx] == ".": 
        y += 1
        
    if y == 0:
        print("covered source")
        return -1
    
    
    if matrix[y][xx-1] == ".":
        return fall2(matrix, y, xx-1)
    elif matrix[y][xx+1] == '.':
        return fall2(matrix, y, xx+1)
    else:
        matrix[y-1][xx] = "o"
        # print_matrix(matrix)
        return 0

def part2(matrix):
    for i in range(100000):
        rc = fall2(matrix, 0, 500)
        if rc == -1:
            print("part 2 ans", i)
            break
    print_matrix(matrix)

if __name__ == "__main__":
    with open("input1.txt") as f:
        txt = f.read().strip()
        line = txt.split("\n")
        strs = [s.split(" -> ") for s in line]
    
    min_x = 600
    max_x = 0
    max_y = 0
    
    # find max and min of grid
    for l in strs:
        for str in l:
            t1, t2 = str.split(",")
            x = int(t1)
            y = int(t2)
            if x < min_x:
                min_x = x
            if y > max_y:
                max_y = y
            if x > max_x:
                max_x = x

    # part1
    # matrix = grid1(strs, min_x, max_x, max_y)
    # part1(matrix)
    
    # part2
    matrix = grid2(strs, min_x, max_x, max_y)
    part2(matrix)
    

    

    


    
    
    
    
    
    
