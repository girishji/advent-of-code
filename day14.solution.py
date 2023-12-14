import copy

with open('day14.input.txt') as f:
    grid = f.readlines()
grid = [list(line.strip()) for line in grid]

rlen, clen = len(grid), len(grid[0])


def north(grd):
    global rlen, clen
    grid = copy.deepcopy(grd)
    for col in range(clen):
        to = 0
        for row in range(rlen):
            while to < row and grid[to][col] != '.':
                to += 1
            if grid[row][col] == '#':
                to = row + 1
            elif grid[row][col] == 'O' and grid[to][col] == '.':
                grid[to][col], grid[row][col] = grid[row][col], grid[to][col]
                to += 1
    return grid


def south(grd):
    global rlen, clen
    grid = copy.deepcopy(grd)
    for col in range(clen):
        to = rlen - 1
        for row in reversed(range(rlen)):
            while to > row and grid[to][col] != '.':
                to -= 1
            if grid[row][col] == '#':
                to = row - 1
            elif grid[row][col] == 'O' and grid[to][col] == '.':
                grid[to][col], grid[row][col] = grid[row][col], grid[to][col]
                to -= 1
    return grid


def east(grd):
    global rlen, clen
    grid = copy.deepcopy(grd)
    for row in grid:
        to = 0
        for ridx in range(rlen):
            while to < ridx and row[to] != '.':
                to += 1
            if row[ridx] == '#':
                to = ridx + 1
            elif row[ridx] == 'O' and row[to] == '.':
                row[ridx], row[to] = row[to], row[ridx]
                to += 1
    return grid


def west(grd):
    global rlen, clen
    grid = [list(reversed(row)) for row in grd]
    # print(grid)
    grid = east(grid)
    grid = [list(reversed(row)) for row in grid]
    return grid


def weight(grid):
    global rlen
    wt = 0
    for col in range(clen):
        for row in range(rlen):
            if grid[row][col] == 'O':
                wt += rlen - row
    return wt


print(weight(north(grid)))

# part 2
count = 1000000000
count = 87 + ((count - 87) % 11) # do visual inspection to get cycle repetition

transformed = copy.deepcopy(grid)
for i in range(count):
    transformed = west(south(east(north(transformed))))
    wt = weight(transformed)
print(wt)
