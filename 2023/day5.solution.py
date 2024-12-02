import itertools
import re

mstr = ['seed-to-soil', 'soil-to-fertilizer', 'fertilizer-to-water',
        'water-to-light', 'light-to-temperature', 'temperature-to-humidity',
        'humidity-to-location']
maps = []

with open('day5.input.txt') as f:
    for line in f:
        if re.match('seeds:', line):
            seeds = [int(x) for x in line.split(':')[1].split()]
        elif re.match(r'({})'.format('|'.join(mstr)), line):
            maps.append([])
        elif re.match(r'\d', line):
            maps[-1].append([int(x) for x in line.strip().split()])

def lookup(s, map):
    for m in map:
        if m[1] <= s < (m[1] + m[2]):
            return m[0] + s - m[1]
    return s

def get_location(src):
    for amap in maps:
        src = lookup(src, amap)
    return src

print(min(get_location(seed) for seed in seeds))

# part 2

def rlookup(s, map):
    for m in map:
        if m[0] <= s < (m[0] + m[2]):
            return m[1] + s - m[0]
    return s

def get_seed(src, k):
    for amap in reversed(maps[:k]):
        src = rlookup(src, amap)
    return src

candidates = seeds[::2]
for k, amap in enumerate(maps):
    for m in amap:
        seed = get_seed(m[1], k)
        if any(s <= seed < s + r for s, r in zip(seeds[::2], seeds[1::2])):
            candidates.append(seed)

print(min(get_location(seed) for seed in candidates))
