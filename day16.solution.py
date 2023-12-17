# BFS is the classic solution to this problem. But I'll solve it using DFS.

from collections import deque, namedtuple
from enum import Enum

with open('day16.input.txt') as f:
    grid = [line.strip() for line in f]

Dir = Enum('Dir', ['L', 'R', 'U', 'D'])
Beam = namedtuple('Beam', ('loc', 'dir'))


def trace(beam, energized):
    if beam in energized or not (0 <= beam.loc[0] < len(grid) and 0 <= beam.loc[1] < len(grid[0])):
        return
    energized.add(beam)
    dot = {Dir.R: (0, 1), Dir.L: (0, -1), Dir.U: (-1, 0), Dir.D: (1, 0)}
    slash = {Dir.R: [(-1, 0), Dir.U], Dir.L: [(1, 0), Dir.D], Dir.U: [(0, 1), Dir.R], Dir.D: [(0, -1), Dir.L]}
    bslash = {Dir.R: [(1, 0), Dir.D], Dir.L: [(-1, 0), Dir.U], Dir.U: [(0, -1), Dir.L], Dir.D: [(0, 1), Dir.R]}

    def locadd(l1, l2):
        return tuple(map(sum, zip(l1, l2)))

    match grid[beam.loc[0]][beam.loc[1]]:
        case '.':
            beam = Beam(locadd(beam.loc, dot[beam.dir]), beam.dir)
        case '/':
            beam = Beam(locadd(beam.loc, slash[beam.dir][0]), slash[beam.dir][1])
        case '\\':
            beam = Beam(locadd(beam.loc, bslash[beam.dir][0]), bslash[beam.dir][1])
        case '-':
            if beam.dir == Dir.L or beam.dir == Dir.R:
                beam = Beam(locadd(beam.loc, dot[beam.dir]), beam.dir)
            else:
                return (Beam(beam.loc, Dir.L), Beam(beam.loc, Dir.R))
        case '|':
            if beam.dir == Dir.U or beam.dir == Dir.D:
                beam = Beam(locadd(beam.loc, dot[beam.dir]), beam.dir)
            else:
                return (Beam(beam.loc, Dir.D), Beam(beam.loc, Dir.U))
    return trace(beam, energized)


def count(beam):
    energized, stack = set(), deque()
    stack.append(beam)
    while stack:
        beams = trace(stack.pop(), energized)
        if beams:
            stack.extend(beams)
    return len(set(en.loc for en in energized))

print(count(Beam((0, 0), Dir.R)))

# part 2

maxcount = 0
rowcount, colcount = len(grid), len(grid[0])
maxcount = max(maxcount, max([count(Beam((row, 0), Dir.R)) for row in range(rowcount)]))
maxcount = max(maxcount, max([count(Beam((row, colcount - 1), Dir.L)) for row in range(rowcount)]))
maxcount = max(maxcount, max([count(Beam((0, col), Dir.D)) for col in range(colcount)]))
maxcount = max(maxcount, max([count(Beam((rowcount - 1, col), Dir.U)) for col in range(colcount)]))
print(maxcount)
