# 题目：3718. 缺失的最小倍数（Smallest Missing Multiple of K）
# 思路：先把数组元素放进集合，再用无限计数器从 k 的 1 倍开始逐个检查，第一个不在集合中的倍数就是答案。
# 时间复杂度：O(n + m)，m 为答案的倍数序号（不超过 n + 1）；空间复杂度：O(n)，用于存放集合。
class Solution:  # LeetCode 约定的题解类
    def missingMultiple(self, nums: List[int], k: int) -> int:  # nums：整数数组；k：倍数基数；返回最小的不在数组中的 k 的正倍数
        s = set(nums)  # 用集合记录数组里出现过的值
        for i in count(1):  # 从 k 的 1 倍开始逐个检查（count(1) 是无限递增计数器）
            x = k * i  # 第 i 个 k 的正倍数
            if x not in s:  # 该倍数不在集合中，即为答案
                return x  # 立刻返回最小缺失倍数
