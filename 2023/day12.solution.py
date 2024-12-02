# part 1
import functools
import re

@functools.cache
def solve(springs, counts):
    if not counts:
        return 1 if re.match(r'[.?]*$', springs) else 0
    if springs.count('#') + springs.count('?') < sum(counts):
        return 0
    pat = r'(?=([?#]{{{}}}(?!#)))'.format(counts[0])
    summ = 0
    for it in re.finditer(pat, springs):
        ss = springs[it.start(): it.start() + counts[0]]
        if ss.count('#') + ss.count('?') + springs[:it.start()].count('#') <= counts[0]:
            summ += solve(springs[it.span()[0] + counts[0] + 1:], tuple(counts[1:]))
    return summ


with open('day12.input.txt') as f:
    sum1, sum2 = 0, 0
    for line in f:
        springs, counts = line.split()
        counts = tuple([int(cn) for cn in counts.split(',')])
        sum1 += solve(springs, counts)
        springs = (springs + '?' + springs + '?' + springs + '?' +
                   springs + '?' + springs)
        counts *= 5
        sum2 += solve(springs, counts)
print(sum1, sum2)
