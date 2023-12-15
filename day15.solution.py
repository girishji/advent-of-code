import functools
import re

with open('day15.input.txt') as f:
    seq = f.readline().strip()

def hash(s):
    return functools.reduce(lambda x, y: ((x + y) * 17) % 256, [ord(ch) for ch in list(s)], 0)

print(sum(hash(step) for step in seq.split(',')))

# part 2

boxes = [[] for _ in range(256)]
for step in seq.split(','):
    if re.search(r'=', step):
        label, fl = step.split('=')
        box = hash(label)
        lens = next((lens for lens in boxes[box] if lens[0] == label), None)
        if lens:
            lens[1] = fl
        else:
            boxes[box].append([label, fl])
    else:
        label, _ = step.split('-')
        box = hash(label)
        lens = next((lens for lens in boxes[box] if lens[0] == label), None)
        if lens:
            boxes[box].remove(lens)

print(sum((i + 1) * (j + 1) * int(lens[1]) for i, box in enumerate(boxes) for j, lens in enumerate(box)))
