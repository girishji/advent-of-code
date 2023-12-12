# part 1
import functools
import re

# part 1
# with open('day12.input.txt') as f:
#     summ = 0
#     for line in f:
#         springs, count = line.split()
#         count = [int(cn) for cn in count.split(',')]
#         unknwn = [i for i, x in enumerate(springs) if x == '?']
#         for cand in itertools.combinations(unknwn, sum(count) - springs.count('#')):
#             spr = [ch if i not in cand else '#' for i, ch in enumerate(springs)]
#             spr = ''.join(spr).replace('?', '.')
#             cnt = [len(cn) for cn in spr.split('.') if cn]
#             if cnt == count:
#                 summ += 1
# print(summ)

# part 1 and 2


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
