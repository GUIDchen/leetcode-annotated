# 题目：2750. 将数组划分成若干好子数组的方式（Ways to Split Array Into Good Subarrays）
# 思路：好子数组必须恰好包含一个 1；相邻两个 1 之间有 i-j 个可选切分位置，按乘法原理把它们累乘起来。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfGoodSubarraySplits(self, nums: List[int]) -> int:  # nums：只含 0/1 的数组；返回划分成好子数组的方案数
        mod = 10**9 + 7  # 模数，防止方案数过大
        ans, j = 1, -1  # ans：方案数（乘法原理累乘）；j：上一个 1 的下标，-1 表示还没遇到 1
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            if x == 0:  # 0 不影响切分点位置，直接跳过
                continue  # 进入下一轮
            if j > -1:  # 不是第一个 1，可以在与上一个 1 之间选择切分点
                ans = ans * (i - j) % mod  # 两个 1 之间有 i-j 个切分位置，乘法原理累乘
            j = i  # 更新上一个 1 的位置
        return 0 if j == -1 else ans  # 没有 1 时无解返回 0，否则返回累乘结果
