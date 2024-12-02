import re

snums = [ 'zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten' ]
pat = re.compile(r'(?=(\d|{}))'.format('|'.join(snums)))
digit = lambda x: int(x) if re.search(r'\d', x) else (snums.index(x) % 10)
sum = 0
with open('day1.input.txt') as f:
    for l in f:
        nums = pat.findall(l)
        if nums:
            sum += digit(nums[0]) * 10 + digit(nums[-1])
print(sum)
