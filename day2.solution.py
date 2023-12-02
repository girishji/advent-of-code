# 12 red cubes, 13 green cubes, and 14 blue cubes

from sys import stderr

sum, power = 0, 0
with open('day2.input.txt') as f:
    for line in f:
        game, draws = line.split(':')
        draws = draws.strip().split(';')
        r, g, b = 0, 0, 0
        for draw in draws:
            groups = draw.strip().split(',')
            for group in groups:
                count, color = group.strip().split()
                count = int(count)
                if color == 'red':
                    r = max(r, count)
                elif color == 'green':
                    g = max(g, count)
                elif color == 'blue':
                    b = max(b, count)
                else:
                    print('failed ' + color, file=stderr)
        power += r * g * b
        if r <= 12 and g <= 13 and b <= 14:
            sum += int(game.split()[1])
            print(game, sum)
print(sum, power)
