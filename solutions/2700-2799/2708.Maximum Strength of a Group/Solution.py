# 题目：2708. 一个小组的最大实力值（Maximum Strength of a Group）
# 思路：n 不超过 13，用位掩码枚举所有非空子集，逐个累乘并记录最大乘积。
# 时间复杂度：O(2^n · n)，共 2^n - 1 个子集、每个子集扫 n 位；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxStrength(self, nums: List[int]) -> int:  # nums 是可选的元素列表
        ans = -inf  # 答案初始化为负无穷，保证任何子集乘积都能刷新它
        for i in range(1, 1 << len(nums)):  # 位掩码枚举所有非空子集（从 1 开始，跳过空集）
            t = 1  # 当前子集的乘积，从 1 开始累乘
            for j, x in enumerate(nums):  # 同时取得下标 j（对应二进制位）与元素值 x
                if i >> j & 1:  # 第 j 位为 1，说明 x 被选入当前子集
                    t *= x  # 把 x 乘入当前子集的乘积
            ans = max(ans, t)  # 更新全局最大实力值
        return ans  # 所有非空子集乘积中的最大值
