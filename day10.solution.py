# day 10

from collections import namedtuple
from sys import stderr

with open('day10.input.txt') as f:
    mmaze = [line.strip() for line in f.readlines()]


Tile = namedtuple('Tile', ('x', 'y'))


def maze(t):
    return mmaze[t.x][t.y]


for i, line in enumerate(mmaze):
    if line.find('S') != -1:
        start = Tile(i, line.find('S'))


def get_next(prev, tile):
    step = {
            ('|', (-1, 0)): (1, 0),
            ('|', (1, 0)): (-1, 0),
            ('-', (0, 1)): (0, -1),
            ('-', (0, -1)): (0, 1),
            ('7', (0, -1)): (1, 0),
            ('7', (1, 0)): (0, -1),
            ('J', (-1, 0)): (0, -1),
            ('J', (0, -1)): (-1, 0),
            ('L', (-1, 0)): (0, 1),
            ('L', (0, 1)): (-1, 0),
            ('F', (1, 0)): (0, 1),
            ('F', (0, 1)): (1, 0),
            }
    if not (tile.x >= 0 and tile.x < len(mmaze) and tile.y >= 0
            and tile.y < len(mmaze[tile.x])):
        return None, None
    key = (maze(tile), (prev.x - tile.x, prev.y - tile.y))
    if key in step:
        nxt = Tile(*(step[key]))
        return tile, Tile(tile.x + nxt.x, tile.y + nxt.y)
    return None, None


def travel(prev, tile):
    path = [prev, tile]
    while tile != start:
        prev, tile = get_next(prev, tile)
        if not prev:
            return []
        path.append(tile)
    return path


for nx, ny in ((1, 0), (-1, 0), (0, 1), (0, -1)):
    nxt = Tile(start.x + nx, start.y + ny)
    path = travel(start, nxt)
    if path:
        print(len(path) // 2)
        break

# part 2

if Tile(start.x - 1, start.y) in path and Tile(start.x + 1, start.y) in path:
    mmaze[start.x] = mmaze[start.x].replace('S', '|')
elif Tile(start.x, start.y - 1) in path and Tile(start.x, start.y + 1) in path:
    mmaze[start.x] = mmaze[start.x].replace('S', '-')
elif Tile(start.x, start.y - 1) in path and Tile(start.x - 1, start.y) in path:
    mmaze[start.x] = mmaze[start.x].replace('S', 'J')
elif Tile(start.x, start.y - 1) in path and Tile(start.x + 1, start.y) in path:
    mmaze[start.x] = mmaze[start.x].replace('S', 'L')
elif Tile(start.x, start.y + 1) in path and Tile(start.x - 1, start.y) in path:
    mmaze[start.x] = mmaze[start.x].replace('S', '7')
elif Tile(start.x, start.y + 1) in path and Tile(start.x + 1, start.y) in path:
    mmaze[start.x] = mmaze[start.x].replace('S', 'F')
else:
    print('error', file=stderr)

icount = 0
for i, row in enumerate(mmaze):
    inside = False
    boundary = set(p for p in path if p.x == i)
    for j in range(len(row)):
        t = Tile(i, j)
        if t in boundary:
            if maze(t) == '|':
                inside = not inside
            else:
                st = maze(t)
                while maze(Tile(i, j + 1)) == '-':
                    j += 1
                end = maze(Tile(i, j + 1))
                if (st, end) in set((('F', 'J'), ('L', '7'))):
                    inside = not inside
        elif inside:
            icount += 1

print(icount)
