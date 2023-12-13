
def reflect(pat):
    for div in range(1, len(pat)):
        for i in range(1, min(div, len(pat) - div) + 1):
            if pat[div - i] != pat[div + i - 1]:
                break
        else:
            return div * 100
    for div in range(1, len(pat[0])):
        for i in range(1, min(div, len(pat[0]) - div) + 1):
            if any(row[div - i] != row[div + i - 1] for row in pat):
                break
        else:
            return div
    return 0


def reflect_defect(pat, excl):
    rexcl, cexcl = excl // 100, excl % 100
    for div in range(1, len(pat)):
        if div == rexcl:
            continue
        skipped = False
        for i in range(1, min(div, len(pat) - div) + 1):
            if pat[div - i] != pat[div + i - 1]:
                diffs = (pat[div - i][j] != pat[div + i - 1][j] for j in range(len(pat[0])))
                if sum(diffs) == 1 and not skipped:
                    skipped = True
                    continue
                break
        else:
            return div * 100
    for div in range(1, len(pat[0])):
        if div == cexcl:
            continue
        skipped = False
        for i in range(1, min(div, len(pat[0]) - div) + 1):
            diffs = [row[div - i] != row[div + i - 1] for row in pat]
            if any(diffs):
                if sum(diffs) == 1 and not skipped:
                    skipped = True
                    continue
                break
        else:
            return div
    return 0


sum1, sum2 = 0, 0


def summ(pattern):
    global sum1, sum2
    div = reflect(pattern)
    sum1 += div
    sum2 += reflect_defect(pattern, div)


with open('day13.input.txt') as f:
    pattern = []
    for line in f:
        if not line.strip():
            summ(pattern)
            pattern = []
        else:
            pattern.append(line.strip())
    summ(pattern)

print(sum1, sum2)
