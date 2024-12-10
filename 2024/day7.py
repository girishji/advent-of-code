with open('./day7.input.txt') as f:
    ares = []
    anums = []
    for l in f:
        s = l.split(':')
        ares.append(int(s[0]))
        anums.append([int(x) for x in s[1].split()])

def accum(a, i, res, nums, concat=False):
    global ans, done
    if done:
        return
    if i == len(nums):
        if a == res:
            ans += res
            done = True
        return
    if a > res:
        return
    na = a + nums[i]
    accum(na, i + 1, res, nums, concat)
    na = a * nums[i]
    accum(na, i + 1, res, nums, concat)
    if concat:
        na = (a * (10 ** len(str(nums[i])))) + nums[i]
        accum(na, i + 1, res, nums, concat)

ans = 0
done = False

for res, nums in zip(ares, anums):
    done = False
    accum(nums[0], 1, res, nums)
print(ans)
ans = 0
for res, nums in zip(ares, anums):
    done = False
    accum(nums[0], 1, res, nums, True)
print(ans)
