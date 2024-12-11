from collections import defaultdict

after = defaultdict(set)
res1 = 0
res2 = 0

def correct_order(pg):
    for i in range(len(pg)):
        for j in range(i + 1, len(pg)):
            if pg[i] in after[pg[j]]:
                pg[i], pg[j] = pg[j], pg[i]
                return correct_order(pg)
    return int(pg[len(pg) // 2])

with open('5.txt') as f:
    for l in f:
        n = l.rstrip().split('|')
        if len(n) == 2:
            after[n[0]].add(n[1])
        else:
            if l.rstrip():
                pg = l.rstrip().split(',')
                for i in reversed(range(len(pg))):
                    if set(pg[0:i]) & after[pg[i]]:
                        break;
                else:
                    res1 += int(pg[len(pg) // 2])
                res2 += correct_order(pg)

print(res1, res2 - res1)
