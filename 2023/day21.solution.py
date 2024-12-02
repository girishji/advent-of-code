import itertools
import math

with open('day21.input.txt') as f:
    grid = [line.strip() for line in f]
rcount, ccount = len(grid), len(grid[0])
S = next((i, j) for i in range(rcount) for j in range(ccount) if grid[i][j] == 'S')

def solve(maxsteps=0):
    global S, rcount, ccount
    dist = 0
    series = []
    seen = set()
    seen.add(S)
    series = []
    for steps in range(500):
        seeing = set()
        for row, col in seen:
            for nbr in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = (row + nbr[0], col + nbr[1])
                if grid[nr % rcount][nc % ccount] in '.S':
                    seeing.add((nr, nc))

        dist += 1
        seen = seeing
        if maxsteps == 64 and dist == maxsteps:
            return len(seen)

        # 26501365 is n * len(grid) + 65 (=len(grid) // 2)
        if (dist - (rcount // 2)) % rcount == 0:
            series.append(len(seen))
    return series

print(solve(64))

# part 2
# very difficult to come up with a general solution. this is aoc, so look at
# the pattern  and solve this particular case. grid is 131x131 with empty tiles
# all around. check if you can predict the series at 65+131, 65+131x2, ... intervals
# using wolfram alfa.
# 26501365 is n * 131 + 65 (== 131 // 2)

series = solve()
print(series)
series1 = [y - x for x, y in itertools.pairwise(series)]
series2 = [y - x for x, y in itertools.pairwise(series1)]
series3 = [y - x for x, y in itertools.pairwise(series2)]
print(series1)
print(series2)
print(series3)
# you can build this series by adding last term of series3 to series2 etc.
# but there is a quicker way:
# The series returned from solve() fits a quadratic series according to worlfram alfa:
# https://www.wolframalpha.com/input?i=3957%2C+35223%2C+97645%2C+191223
# it says the closed form is:
# a_n = 15578 n^2 - 15468 n + 3847 (for all terms given)

n = math.floor(26501365 // rcount) + 1
p2soln = 15578 * (n ** 2) - 15468 * n + 3847
print(p2soln)
