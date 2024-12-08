from itertools import product

grid = []
with open('./day6.input.txt') as f:
    grid = [list(l.strip()) for l in f]
for i, j in product(range(len(grid)), range(len(grid[0]))):
    if grid[i][j] == '^':
        start = (i, j)
res2 = 0
in_range = lambda i, j: 0 <= i < len(grid) and 0 <= j < len(grid[0])

def walk(start):
    dr, dc = -1, 0
    seen = set([(start, (dr, dc))])
    cur = start
    while True:
        i, j = cur[0] + dr, cur[1] + dc
        if not in_range(i, j):
            return (seen, 0)
        if grid[i][j] == '#':
            dr, dc = dc, -dr
            continue
        cur = (i, j)
        if (cur, (dr, dc)) in seen:
            return (seen, 1)
        seen.add((cur, (dr, dc)))

visited = set(item[0] for item in walk(start)[0])
print(len(visited))

res2 = 0
for pos in visited:
    i, j = pos[0], pos[1]
    grid[i][j] = '#'
    res2 += walk(start)[1]
    grid[i][j] = '.'

print(res2)
