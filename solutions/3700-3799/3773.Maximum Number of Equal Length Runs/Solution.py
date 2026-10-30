# 3773. 最大等长连续字符组 / Maximum Number of Equal Length Runs
# 核心思路：用 groupby 把字符串切成若干段连续相同字符，统计每种段长度出现的次数，答案即出现次数的最大值。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为字符串长度。
class Solution:  # 定义题解类
    def maxSameLengthRuns(self, s: str) -> int:  # 返回出现次数最多的“等长连续字符组”的组数
        cnt = Counter()  # 记录每种段长度分别出现过多少次
        for _, g in groupby(s):  # 逐个遍历连续相同字符组成的段
            cnt[len(list(g))] += 1  # 把该长度的出现次数加一
        return max(cnt.values())  # 返回最大的出现次数
