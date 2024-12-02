# Dijkshtra

from collections import namedtuple
import heapq

with open('day17.input.txt') as f:
    Heat = [line.strip() for line in f]

rowcount, colcount = len(Heat), len(Heat[0])

def heat(t):
    global Heat
    return int(Heat[t[0]][t[1]])

def valid_block(b):
    return 0 <= b[0] < rowcount and 0 <= b[1] < colcount

seen = set()
priority_que = []
entry_finder = {}
Entry = namedtuple('Entry', 'heatsum steps block parent')
source = Entry(0, 1, (0, 0), (0, -1))
entry_finder[source[1:]] = source
heapq.heappush(priority_que, source)

def get_entries1(entry):
    entries = []
    for step in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
        nxt = tuple(map(sum, zip(entry.block, step)))
        if not valid_block(nxt) or nxt == entry.parent:
            continue
        if any(a == b == c for a, b, c in zip(nxt, entry.block, entry.parent)):
            if entry.steps == 3:
                continue
            else:
                entries.append(Entry(entry.heatsum + heat(nxt), entry.steps + 1, nxt, entry.block))
        else:
            entries.append(Entry(entry.heatsum + heat(nxt), 1, nxt, entry.block))
    return entries


def least_heat(get_entries):
    global seen, priority_que, entry_finder
    while priority_que:
        entry = heapq.heappop(priority_que)
        if entry.block == (rowcount - 1, colcount - 1):
            print('destination', entry)
            break
        seen.add(entry[1:])
        del entry_finder[entry[1:]]

        for new_entry in get_entries(entry):
            if new_entry[1:] in seen:
                continue
            if new_entry[1:] in entry_finder:
                if entry_finder[new_entry[1:]].heatsum > new_entry.heatsum:
                    entry_finder[new_entry[1:]].heatsum = new_entry.heatsum
                    heapq.heapify(priority_que)
            else:
                heapq.heappush(priority_que, new_entry)
                entry_finder[new_entry[1:]] = new_entry

least_heat(get_entries1)

# part 2

seen = set()
priority_que = []
entry_finder = {}
source = Entry(sum(heat((0, col)) for col in range(1, 4)), 4, (0, 3), (0, 0))
entry_finder[source[1:]] = source
heapq.heappush(priority_que, source)
source = Entry(sum(heat((row, 0)) for row in range(1, 4)), 4, (3, 0), (0, 0))
entry_finder[source[1:]] = source
heapq.heappush(priority_que, source)

def get_entries_inner(en, equalrows=True):
    new_entries = []
    if en.steps < 10:
        if equalrows:
            nxt = (en.block[0], en.block[1] + (1 if en.parent[1] < en.block[1] else -1))
        else:
            nxt = (en.block[0] + (1 if en.parent[0] < en.block[0] else -1), en.block[1])
        if valid_block(nxt):
            new_entries.append(Entry(en.heatsum + heat(nxt), en.steps + 1, nxt, en.block))
    if equalrows:
        nxt1, nxt2 = (en.block[0] + 4, en.block[1]), (en.block[0] - 4, en.block[1])
    else:
        nxt1, nxt2 = (en.block[0], en.block[1] + 4), (en.block[0], en.block[1] - 4)
    for nxt in [(nxt1, 'plus'), (nxt2, 'minus')]:
        if valid_block(nxt[0]):
            heatadd = 0
            for idx in range(1, 5):
                if nxt[1] == 'plus':
                    nextblk = (en.block[0] + idx, en.block[1]) if equalrows else (en.block[0], en.block[1] + idx)
                else:
                    nextblk = (en.block[0] - idx, en.block[1]) if equalrows else (en.block[0], en.block[1] - idx)
                heatadd += heat(nextblk) if valid_block(nextblk) else 0
            new_entries.append(Entry(en.heatsum + heatadd, 4, nxt[0], en.block))
    return new_entries

def get_entries2(entry):
    if entry.block[0] == entry.parent[0]:
        return get_entries_inner(entry, True)
    return get_entries_inner(entry, False)

least_heat(get_entries2)
