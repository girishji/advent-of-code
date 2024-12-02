import functools
import math

with open('day6.input.txt') as f:
    lines = f.readlines()
    time = lines[0].split()[1:]
    distance = lines[1].split()[1:]


def ways(T, D):
    sroot = math.sqrt(T * T - 4 * D)
    t1 = (T + sroot) / 2
    t2 = (T - sroot) / 2
    epsilon = 0.0000000001
    return math.floor(t1 - epsilon) - math.ceil(t2 + epsilon) + 1


print(functools.reduce(lambda x, y: x * y,
                       (ways(T, D) for T, D in zip(map(int, time), map(int, distance)))))


# part 2
nint = int(''.join(time))
ndist = int(''.join(distance))
print(ways(nint, ndist))
