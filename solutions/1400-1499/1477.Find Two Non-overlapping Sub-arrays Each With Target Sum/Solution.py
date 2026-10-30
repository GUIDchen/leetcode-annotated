# 题目：1477. 找两个和为目标值且不重叠的子数组（Find Two Non-overlapping Sub-arrays Each With Target Sum）
# 思路：前缀和 + 哈希表。d 记录「前缀和 → 最早出现的前缀下标」，f[i] 表示前 i 个元素中和为 target 的最短子数组长度；扫到 i 时把以 i 结尾的子数组与它起点之前的最优子数组拼起来更新答案。
# 时间复杂度：O(n)，每个元素只扫一次；空间复杂度：O(n)，哈希表与 f 数组。
class Solution:  # LeetCode 约定的题解类
    def minSumOfLengths(self, arr: List[int], target: int) -> int:  # arr：输入数组；target：子数组目标和
        d = {0: 0}  # 哈希表：键是前缀和，值是它出现的位置（前缀下标）；空前缀和为 0、位置 0
        s, n = 0, len(arr)  # s：当前前缀和；n：数组长度
        f = [inf] * (n + 1)  # f[i]：只考虑前 i 个元素时，和为 target 的最短子数组长度
        ans = inf  # 两个不重叠子数组长度之和的最小值，初值取无穷大
        for i, v in enumerate(arr, 1):  # i 是前缀下标（从 1 开始），v 是当前元素
            s += v  # 累加得到当前前缀和
            f[i] = f[i - 1]  # 先继承「不选以 i 结尾的子数组」时的最优长度
            if s - target in d:  # 该前缀和以前出现过，说明存在以 i 结尾、和为 target 的子数组
                j = d[s - target]  # j 是该子数组起点的前缀下标
                f[i] = min(f[i], i - j)  # 更新前缀最优长度：取更短的那个
                ans = min(ans, f[j] + i - j)  # 用「j 之前的最优子数组」与「当前子数组」拼成不重叠的两段
            d[s] = i  # 记录当前前缀和的位置（覆盖旧值，保证子数组尽量短）
        return -1 if ans > n else ans  # 答案超过数组长度说明凑不出两段，返回 -1
