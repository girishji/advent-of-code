# day 11

from functools import cache
from collections import deque

with open('./11.txt') as f:
    stones = next(f).split()

@cache
def nxt(s):
    if s == '0':
        return ['1']
    elif len(s) % 2 == 0:
        return [str(int(s[0 : len(s) // 2])), str(int(s[len(s) // 2 : ]))]
    else:
        return [str(int(s) * 2024)]

def blink(stones):
    tmp = []
    for s in stones:
        tmp += nxt(s)
    return tmp

# part 1
after = stones
for _ in range(75):
    after = blink(after)
print(len(after))
