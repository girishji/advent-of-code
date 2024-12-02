
import functools
import itertools

def series_next(series):
    first, last = [series[0]], [series[-1]]
    diffs = series
    while any(diffs):
        diffs = [j -i for i, j in itertools.pairwise(diffs)]
        first.append(diffs[0])
        last.append(diffs[-1])
    return functools.reduce(lambda x, y: y - x, reversed(first)), sum(last)


with open('day9.input.txt') as f:
    summ = [0, 0]
    for line in f:
        first, last = series_next([int(x) for x in line.split()])
        summ = [summ[0] + first, summ[1] + last]
    print(summ)
