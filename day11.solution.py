import itertools
import re

with open('day11.input.txt') as f:
    grid = [line.strip() for line in f.readlines()]

erows = [row for row in range(len(grid)) if re.match(r'\.+$', grid[row])]
ecols = [col for col in range(len(grid[0])) if all(row[col] == '.' for row in grid)]
galaxies = [(r, c) for r in range(len(grid)) for c in range(len(grid[0])) if grid[r][c] == '#']

for expand in [1, (1000000 - 1)]:
    summ = 0
    for ga, gb in itertools.combinations(galaxies, 2):
        summ += abs(ga[0] - gb[0]) + abs(ga[1] - gb[1])
        summ += expand * len(set(erows) & set(range(min(ga[0], gb[0]) + 1, max(ga[0], gb[0]))))
        summ += expand * len(set(ecols) & set(range(min(ga[1], gb[1]) + 1, max(ga[1], gb[1]))))
    print(summ)
