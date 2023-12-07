from collections import namedtuple
import itertools

with open('day7.input.txt') as f:
    lines = f.readlines()

Hand = namedtuple('Hand', ('cards', 'bid'))
hands = [Hand(*(line.split())) for line in lines]

def type(hand):
    counts = (len(list(gr)) for _, gr in itertools.groupby(sorted(list(hand.cards))))
    strength = [[1, 1, 1, 1, 1], [1, 1, 1, 2], [1, 2, 2], [1, 1, 3], [2, 3], [1, 4], [5]]
    return strength.index(sorted(counts))

def strength(hand):
    weak2strong = ['A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'][::-1]
    return [weak2strong.index(card) for card in list(hand.cards)]

def summ(fn1, fn2):
    global hands
    decorated = [(fn1(h), fn2(h), h) for h in hands]
    decorated.sort()
    hands = [hand for _, _, hand in decorated]
    res = 0
    for i, hand in enumerate(hands):
        res += (i + 1) * int(hand.bid)
    return res

print(summ(type, strength))

# part 2
def strength2(hand):
    weak2strong = ['A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'][::-1]
    return [weak2strong.index(card) for card in list(hand.cards)]

def type2(hand):
    counts = {ch: len(list(gr)) for ch, gr in itertools.groupby(sorted(list(hand.cards)))}
    key = [cnt for ch, cnt in counts.items() if ch != 'J']
    key.sort()
    if 'J' in counts:
        if not key:
            key.append(counts['J'])
        else:
            key[-1] += counts['J']
    strength = [[1, 1, 1, 1, 1], [1, 1, 1, 2], [1, 2, 2], [1, 1, 3], [2, 3], [1, 4], [5]]
    return strength.index(key)

print(summ(type2, strength2))
