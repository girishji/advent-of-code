import random

items = [(k, v) for k, vs in [ln.split(': ') for ln in open('day25.input.txt').read().split('\n') if ln] for v in vs.split()]
wires = set()
for x, y in items:
    if (x, y) not in wires and (y, x) not in wires:
        wires.add((x, y))

# https://en.wikipedia.org/wiki/Karger%27s_algorithm

vertices = set([n[0] for n in wires] + [n[1] for n in wires])

while True:
    groups = [set([n]) for n in vertices]
    edges = list(wires.copy())
    while len(groups) > 2:
        s, t = edges[random.randrange(len(edges))]
        sgr = next(group for group in groups if s in group)
        tgr = next(group for group in groups if t in group)
        groups = [group for group in groups if s not in group and t not in group] + [sgr | tgr]
        nedges = set()
        for x, y in edges:
            x = s if x == t else x
            y = s if y == t else y
            if (x, y) not in nedges and (y, x) not in nedges and x != y:
                nedges.add((x, y))
        edges = list(nedges)
    if len(groups) == 2:
        if sum((wire[0] in groups[0] and wire[1] in groups[1]) or (wire[0] in groups[1] and wire[1] in groups[0]) for wire in wires) == 3:
            print(len(groups[0]) * len(groups[1]))
            break
