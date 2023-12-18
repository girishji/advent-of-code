# Trapezoid formula or Shoelace formula (https://en.wikipedia.org/wiki/Shoelace_formula)

# part 1

def area(trench):
    area = 0
    r1, c1 = 0, 0
    step = {'R': (0, 1), 'L': (0, -1), 'D': (1, 0), 'U': (-1, 0)}
    for dir, dist in trench:
        dist = int(dist)
        r2, c2 = r1 + step[dir][0] * dist, c1 + step[dir][1] * dist
        area += (dist if dir in ('R', 'D') else 0)
        if dir in ['L', 'R']:
            area += (c1 - c2) * r1
        r1, c1 = r2, c2
    return (area + 1)

with open('day18.input.txt') as f:
    print(area(ln.strip().split()[:-1] for ln in f))

# part 2

dircode = {0: 'R', 1: 'D', 2: 'L', 3: 'U'}
with open('day18.input.txt') as f:
    print(area((dircode[int(color[~1])], int(color[2:-2], base=16)) for _, _, color in (ln.strip().split() for ln in f)))
