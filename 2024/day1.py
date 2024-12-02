with open('day1.input.txt') as f:
    l1 = []
    l2 = []
    for line in f:
        i1, i2 = line.split()
        l1.append(int(i1))
        l2.append(int(i2))
    res = sum(abs(x1 - x2) for x1, x2 in zip(sorted(l1), sorted(l2)))
    print(res)
