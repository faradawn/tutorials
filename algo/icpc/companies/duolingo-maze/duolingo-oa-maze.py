from collections import defaultdict, deque

def backtrace(parent, start, end):
    """ reconstruct the bfs path """
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
            else:
                resStr.append("south")
        elif cury == y:
            if curx > x:
                resStr.append("east")
            else:
                resStr.append("west")
        
        x = curx
        y = cury
        
    return resStr
                
    

def shorten_path(original_path: List[str]) -> List[str]:
    """Find the shortest path through the maze given the steps Duo took.

    Parameters:
        original_path: The list of steps Duo took through a maze.
            Containts only the string literals 'north', 'east', 'south',
            and 'west'.

    Returns:
        A shorter path of steps through the maze containing only the
        string literals 'north', 'east', 'south', and 'west'.
    """
    # print("intput", original_path)
    
    x = 0
    y = 0
    prev = "0,0"
    adj = defaultdict(list)
    
    for s in original_path:
        if s == "south": y -= 1
        elif s == "north": y += 1
        elif s == "west": x-= 1
        elif s == "east": x += 1
        
        if prev not in adj:
            adj[prev] = []
        
        cur = str(x) + ',' + str(y)
        if cur not in adj:
            adj[cur] = []
        
        if str(x-1)+','+str(y) in adj:
            adj[str(x-1)+','+str(y)].append(cur)
            adj[cur].append(str(x-1)+','+str(y))
        if str(x+1)+','+str(y) in adj:
            adj[str(x+1)+','+str(y)].append(cur)
            adj[cur].append(str(x+1)+','+str(y))
        if str(x)+','+str(y-1) in adj:
            adj[str(x)+','+str(y-1)].append(cur)
            adj[cur].append(str(x)+','+str(y-1))
        if str(x)+','+str(y+1) in adj:
            adj[str(x)+','+str(y+1)].append(cur)
            adj[cur].append(str(x)+','+str(y+1))
            
        prev = cur
    
    
    # dfs
    
    visited = {}
    parent = {} # for backtrace path
    q = deque()
    q.append("0,0")
    
    print("adj", adj["0,-1"], adj["7,-1"], adj["7,-7"])
    
    while q:
        for i in range(len(q)):
            cur = q.popleft()
            if cur == prev:
                return backtrace(parent, cur, "0,0")
            for t in adj[cur]:
                if t not in visited:
                    q.append(t)
                    parent[t] = cur
                    visited[t] = 1
    
    return []
        