from collections import namedtuple

with open('day22.input.txt') as f:
    bricks = [line.strip().split('~') for line in f]

Cube = namedtuple('Cube', 'x y z')
Brick = namedtuple('Brick', 'b e')

bricks = [Brick(Cube(*(map(int, be.strip().split(',')))), Cube(*(map(int, en.strip().split(','))))) for be, en in bricks]

def get_cubes(br):
    rng = lambda idx: range(br.b[idx], br.e[idx] + 1)
    return [Cube(x, y, z) for x in rng(0) for y in rng(1) for z in rng(2)]

def collapse(brks):
    nbricks = []
    count = 0
    maxof = lambda idx: max(max(br.b[idx], br.e[idx]) for br in brks)
    grid = [[[None for z in range(maxof(2) + 2)] for y in range(maxof(1) + 1)] for x in range(maxof(0) + 1)]
    for br in sorted(brks, key=lambda br: min(br.b.z, br.e.z)):
        fell = False
        while min(br.b.z, br.e.z) > 1 and all(not grid[cb.x][cb.y][cb.z - 1] for cb in get_cubes(br)):
            br = Brick(Cube(br.b.x, br.b.y, br.b.z - 1), Cube(br.e.x, br.e.y, br.e.z - 1))
            fell = True
        if fell:
            count += 1
        nbricks.append(br)
        for cb in get_cubes(br):
            grid[cb.x][cb.y][cb.z] = br
    return (count, nbricks)

count, nbricks = collapse(bricks)
bricks = nbricks

p1soln, p2soln = 0, 0
for br in bricks:
    brks = [b for b in bricks if br != b]
    count, _ = collapse(brks)
    if count == 0:
        p1soln += 1
    else:
        p2soln += count

print(p1soln, p2soln)
