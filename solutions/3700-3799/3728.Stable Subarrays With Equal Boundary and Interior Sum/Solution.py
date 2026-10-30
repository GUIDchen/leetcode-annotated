# 3728. Stable Subarrays With Equal Boundary and Interior Sum（边界与内部和相等的稳定子数组）
# 核心思路：用前缀和表示区间和，把“左边界特征”(capacity[l], capacity[l]+s[l+1]) 与“右边界特征”(capacity[r], s[r]) 做成哈希 key，特征相同即说明边界值相等且内部和等于边界值，边扫边计数。
# 复杂度：时间 O(n)，空间 O(n)（前缀和数组与哈希表）。

class Solution:
    def countStableSubarrays(self, capacity: List[int]) -> int:  # 统计满足“边界值等于内部和”的稳定子数组个数
        s = list(accumulate(capacity, initial=0))  # 构造前缀和，s[i] = capacity[0..i-1] 之和，长度为 n+1
        n = len(capacity)  # 取数组长度 n
        ans = 0  # 稳定子数组的计数
        cnt = defaultdict(int)  # 哈希表：左边界特征 -> 出现次数
        for r in range(2, n):  # 枚举右端点 r，从 2 开始以保证内部至少有一个元素
            l = r - 2  # 左端点 l 比 r 小 2，随 r 同步后移
            cnt[(capacity[l], capacity[l] + s[l + 1])] += 1  # 记录左边界特征 (capacity[l], capacity[l] + s[l+1])
            ans += cnt[(capacity[r], s[r])]  # 存在相同特征的左端点则累加其个数（边界和等于内部和）
        return ans  # 返回稳定子数组个数
