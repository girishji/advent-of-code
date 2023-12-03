
import re

sum = 0
symbols = set()
with open('day3.input.txt') as f:
    for line in f:
        symbols |= set(re.findall(r'[^.0-9]', line))
    symbols.remove('\n')
    f.seek(0)
    lines = f.readlines()

grsum = 0

for lnum, line in enumerate(lines):
    syms = re.finditer(r'\*', line)
    for s in syms:
        for sidx in range(*(s.span())):
            adj = []
            nums = re.finditer(r'\d+', line)
            for num in nums:
                if sidx + 1 == num.start() or sidx == num.end():
                    adj.append(num.group())
            for adjline in [lines[lnum - 1] if lnum >= 1 else '',
                            lines[lnum + 1] if lnum + 1 < len(lines) else '']:
                nums = re.finditer(r'\d+', adjline)
                for num in nums:
                    if num.start() - 2 < sidx < num.end() + 1:
                        adj.append(num.group())
            if len(adj) == 2:
                grsum += int(adj[0]) * int(adj[1])

for lnum, line in enumerate(lines):
    matches = re.finditer(r'\d+', line)
    for m in matches:
        st, en = m.start(), m.end()
        if lnum >= 1:
            prevl = lines[lnum - 1]
            for i in range(max(0, st - 1), min(en + 1, len(prevl))):
                if prevl[i] in symbols:
                    sum += int(m.group())
                    break
        for i in [max(0, st - 1), min(en, len(line) - 1)]:
            if line[i] in symbols:
                sum += int(m.group())
                break
        if lnum + 1 < len(lines):
            nextl = lines[lnum + 1]
            for i in range(max(0, st - 1), min(en + 1, len(nextl))):
                if nextl[i] in symbols:
                    sum += int(m.group())
                    break

print(sum, grsum)
