import collections
from collections import deque
import itertools
import sys

with open('day23.input.txt') as f:
    maze = [ln.strip() for ln in f]

rc, cc = len(maze), len(maze[0])
S, E = (0, 1), (rc - 1, cc - 2)

sys.setrecursionlimit(rc * cc + 1)

maxdist = 0
steps = dict(zip(('.', '<', '>', '^', 'v'), (((0, 1), (0, -1), (1, 0), (-1, 0)), ((0, -1),), ((0, 1),), ((-1, 0),), ((1, 0),))))
def dfs(loc, prev, dist):
    global maxdist, steps
    tile = maze[loc[0]][loc[1]]
    if not (0 <= loc[0] < cc and 0 <= loc[1] < rc) or tile == '#':
        return
    if loc == E:
        maxdist = max(maxdist, dist)
        return
    for step in steps[tile]:
        nxt = (loc[0] + step[0], loc[1] + step[1])
        if not prev or nxt != prev:
            dfs(nxt, loc, dist + 1)

dfs(S, None, 0)
print(maxdist)

# part 2

def neighbors(r, c):
    global rc, cc
    steps = ((r + st[0], c + st[1]) for st in ((0, 1), (0, -1), (1, 0), (-1, 0)))
    return [(nxr, nxc) for nxr, nxc in steps if 0 <= nxr < rc and 0 <= nxc < cc and maze[nxr][nxc] != '#']

graph = {S: neighbors(*S), E: neighbors(*E)}
for r, c in filter(lambda x: maze[x[0]][x[1]] != '#', itertools.product(range(rc), range(cc))):
    if len(neighbors(r, c)) > 2:
        graph[(r, c)] = set(neighbors(r, c))

ngraph = collections.defaultdict(dict)
for node, lst in graph.items():
    for nxt in lst:
        dist, prev = 1, node
        while nxt not in graph:
            nnxt = next(n for n in neighbors(*nxt) if n != prev)
            prev, nxt = nxt, nnxt
            dist += 1
        ngraph[node][nxt] = dist

graph = ngraph

def allpaths():
    stack = deque()
    stack.append([S, 0, set()])
    maxdist = 0
    while stack:
        node, dist, seen = stack.pop()
        if node == E:
            maxdist = max(maxdist, dist)
            continue
        for nbr, wt in graph[node].items():
            if nbr in seen or nbr in stack:
                continue
            stack.append([nbr, dist + wt, seen | set([node])])
    return maxdist

print(allpaths())


# SLOW solution

def dfs2(loc, prev, seen, dist):
    global maxdist
    tile = maze[loc[0]][loc[1]]
    if not (0 <= loc[0] < cc and 0 <= loc[1] < rc) or tile == '#' or loc in seen:
        return
    if loc == E:
        if maxdist < dist:
            maxdist = dist
            print('maxdist', maxdist)
        return
    nxts = []
    for step in ((0, 1), (0, -1), (1, 0), (-1, 0)):
        nxt = (loc[0] + step[0], loc[1] + step[1])
        if (not prev or nxt != prev) and maze[nxt[0]][nxt[1]] != '#' and nxt not in seen:
            nxts.append(nxt)
    if len(nxts) == 1:
        dfs2(nxts[0], loc, seen, dist + 1)
    else:
        for nxt in nxts:
            dfs2(nxt, loc, seen | set([loc]), dist + 1)

# dfs2(S, None, set(), 0)
# print(maxdist)
