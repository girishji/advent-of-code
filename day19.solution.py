import functools
import re
from sys import stderr

with open('day19.input.txt') as f:
    in_workflow = True
    workflow, parts = {}, []
    for line in f:
        if not line.strip():
            in_workflow = False
            continue
        if in_workflow:
            wf = line.strip().split('{')
            workflow[wf[0]] = wf[1][:-1].split(',')
        else:
            parts.append(line.strip()[1:-1].split(','))

summ = 0
for ratings in parts:
    scope = {}
    for r in (rat.split('=') for rat in ratings):
        scope[r[0]] = int(r[1])
    wf = workflow['in']
    while wf:
        for arule in wf:
            token = None
            if re.search(r':', arule):
                rule, nxt = arule.split(':')
                if eval(rule, scope.copy()):
                    token = nxt
            else:
                token = arule
            if token:
                if token == 'A':
                    summ += sum(scope.values())
                    wf = None
                elif token == 'R':
                    wf = None
                else:
                    wf = workflow[token]
                break

print(summ)

# part 2: DFS

summ = 0

def dfs(token, ratings):
    global summ, workflow
    if token == 'A':
        summ += functools.reduce(lambda x, y: x * y, [rng[1] - rng[0] + 1 for rng in ratings.values()])
        return
    elif token == 'R':
        return
    for arule in workflow[token]:
        if re.search(r':', arule):
            rule, nxt = arule.split(':')
            ll, rr = ratings[rule[0]]
            if rule[1] == '<':
                rmax = int(rule[2:])
                if rr < rmax:
                    dfs(nxt, ratings)
                elif ll < rmax <= rr:
                    rat = ratings.copy()
                    rat[rule[0]] = [ll, rmax - 1]
                    dfs(nxt, rat)
                    ratings[rule[0]] = [rmax, rr]
            elif rule[1] == '>':
                rmin = int(rule[2:])
                if ll > rmin:
                    dfs(nxt, ratings)
                elif ll <= rmin < rr:
                    rat = ratings.copy()
                    rat[rule[0]] = [rmin + 1, rr]
                    dfs(nxt, rat)
                    ratings[rule[0]] = [ll, rmin]
            else:
                print('error', file=stderr)
                exit(1)
        else:
            dfs(arule, ratings)


dfs('in', dict((token, [1, 4000]) for token in ('x', 'm', 'a', 's')))
print(summ)
