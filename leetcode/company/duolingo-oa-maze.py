from collections import defaultdict, deque

def backtrace(parent, start, end):
    resPath = []
    while start != end:
        resPath.append(start)
        start = parent[start]
    
    x = 0
    y = 0
    
    resStr = []
    
    for cur in reversed(resPath):
        curx, cury = cur.split(',')
        curx = int(curx)
        cury = int(cury)
        
        if curx == x:
            if cury > y:
                resStr.append("north")
            elif cury < y:
                resStr.append("south")
        elif cury == y:
            if curx > x:
                resStr.append("east")
            elif curx < x:
                resStr.append("west")
        x = curx
        y = cury
        
    return resStr

        
def solution(path):
    x = 0
    y = 0
    prev = str(0) + ',' + str(0)
    adj = defaultdict(list)
    
    for s in path:
        if s == "south": y -= 1
        elif s == "north": y += 1
        elif s == "west": x -= 1
        elif s == "east": x += 1
        
        if prev not in adj:
            adj[prev] = []
        
        cur = str(x)+','+str(y)
        
        if str(x-1)+','+str(y) in adj:
            adj[str(x-1)+','+str(y)].append(cur)
        if str(x+1)+','+str(y) in adj:
            adj[str(x+1)+','+str(y)].append(cur)
        if str(x)+','+str(y-1) in adj:
            adj[str(x)+','+str(y-1)].append(cur)
        if str(x)+','+str(y+1) in adj:
            adj[str(x)+','+str(y+1)].append(cur)
        
        prev = cur
    
    # start dfs
    endnode = prev
    visited = {}
    parent = {}
    q = deque()
    q.append("0,0")
    
    while q:
        for i in range(len(q)):
            cur = q.popleft()
            if cur == endnode:
                return backtrace(parent, cur, "0,0")
            for t in adj[cur]:
                if t not in visited:
                    q.append(t)
                    parent[t] = cur
                    visited[t] = 1

# test case 1
myinput = ["south", "east", "east", "south", "south", "west", "west", "east", "east", "south"]

# test case 2
myinput = []
temp = ["south"]*3
myinput += temp
temp = ["east"]*5
myinput += temp
temp = ["south"]*2
myinput += temp
temp = ["west"]*5
myinput += temp
temp = ["south"]*2
myinput += temp
temp = ["east"]*2
myinput += temp
temp = ["north"]*2
myinput += temp
temp = ["east"]*3
myinput += temp
temp = ["north"]*2
myinput += temp
temp = ["west"]*5
myinput += temp
temp = ["north"]*2
myinput += temp
temp = ["east"]*7
myinput += temp
temp = ["south"]*8
myinput += temp

# test case 3
myinput = ["south","south","south","south","east","north","east","south","east", "north","north","east"]

res = solution(myinput)
print(res)