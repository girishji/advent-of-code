import re

csum, count = 0, 0
with open('day4.input.txt') as f:
    cards = {}
    for line in f:
        card, cnums = line.split(':')
        card = int(re.search(r'\d+', card).group())
        cards[card] = cards.get(card, 0) + 1
        wnums, nums = cnums.split('|')
        wnums = set(filter(None, wnums.split()))
        nums = set(filter(None, nums.split()))
        n = len(wnums & nums)
        if n:
            csum += 2 ** (n - 1)
            for i in range(1, n + 1):
                cards[i + card] = cards.get(i + card, 0) + cards[card]
print(csum, sum(cards.values()))
