from collections import namedtuple
import math
import re

with open('day8.input.txt') as f:
    lines = f.readlines()
turns = lines[0].strip()
mapp = {}
Turn = namedtuple('Turn', ('L', 'R'))
for line in lines[2:]:
    m = re.search(r'(\w+) = \((\w+), (\w+)\)', line)
    mapp[m.group(1)] = Turn(m.group(2), m.group(3))

def steps(start, dest):
    idx = 0
    while start not in dest:
        start = mapp[start].L if turns[idx % len(turns)] == 'L' else mapp[start].R
        idx += 1
    return idx
print(steps('AAA', set(['ZZZ'])))

# part 2

starts = [n for n in mapp if n.endswith('A')]
dests = set(n for n in mapp if n.endswith('Z'))
print(math.lcm(*([steps(st, dests) for st in starts])))
