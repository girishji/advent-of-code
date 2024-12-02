
from collections import deque, namedtuple
import copy
from dataclasses import dataclass
import math

@dataclass
class Mod:
    typ: str
    st: str
    out: list

ckt, conj = {'button': Mod('', '', ['broadcaster'])}, {}

with open('day20.input.txt') as f:
    for line in f:
        name, out = line.strip().split(' -> ')
        out = [m.strip() for m in out.split(',')]
        if name[0] == '%':
            ckt[name[1:]] = Mod('F', 'L', out)
        elif name[0] == '&':
            ckt[name[1:]] = Mod('C', 'H', out)
            conj[name[1:]] = {}
        else:
            ckt[name] = Mod('', 'L', out)

for name, mod in ckt.items():
    for outm in mod.out:
        if outm in conj:
            conj[outm][name] = 'L'

Pulse = namedtuple('Pulse', 'fr to st')

que = deque()
count = {'H': 0, 'L': 0}

def bfs(stop_at=''):
    itercount = 1
    while que:
        pulse = que.popleft()
        if stop_at and pulse.fr == stop_at and pulse.st == 'H':
            return True
        itercount += 1
        count[pulse.st] += 1
        if pulse.to not in ckt:
            continue
        forward = False
        if ckt[pulse.to].typ == 'F' and pulse.st == 'L':
            ckt[pulse.to].st = 'L' if ckt[pulse.to].st == 'H' else 'H'
            forward = True
        elif ckt[pulse.to].typ == 'C':
            conj[pulse.to][pulse.fr] = pulse.st
            if all(val == 'H' for val in conj[pulse.to].values()):
                ckt[pulse.to].st = 'L'
            else:
                ckt[pulse.to].st = 'H'
            forward = True
        elif ckt[pulse.to].typ == '':
            forward = True
        if forward:
            for dest in ckt[pulse.to].out:
                que.append(Pulse(pulse.to, dest, ckt[pulse.to].st))

init_ckt = copy.deepcopy(ckt)

button_press_count = 1
while True:
    que.append(Pulse('button', 'broadcaster', 'L'))
    bfs()
    if ((all(m.st == 'H' for m in ckt.values() if m.typ == 'C') and
       all(m.st == 'L' for m in ckt.values() if m.typ == 'F')) or
        button_press_count >= 1000):
        break
    button_press_count += 1

print(count['H'] * count['L'])

# part 2
# Plot the diagram of what feeds into 'rx' at least 2 levels

before_rx = [name for name, mod in ckt.items() if 'rx' in mod.out]
before_before_rx = [name for name, mod in ckt.items() if before_rx[0] in mod.out]
def when_High(mod):
    global ckt, conj
    ckt = copy.deepcopy(init_ckt)
    for v in conj.values():
        for m in v:
            v[m] = 'L'
    for i in range(1, 10000):
        que.append(Pulse('button', 'broadcaster', 'L'))
        if bfs(mod):
            return i
    return -1

print(math.lcm(*[when_High(mname) for mname in before_before_rx]))
