# 题目：1646. 获取生成数组中的最大值（Get Maximum in Generated Array）
# 思路：按题意递推，偶数下标取 nums[i/2]，奇数下标取 nums[i/2] + nums[i/2+1]，生成完整数组后取最大值。
# 时间复杂度：O(n)，线性生成加一次扫描；空间复杂度：O(n)，保存生成的数组。
class Solution:  # LeetCode 约定的题解类
    def getMaximumGenerated(self, n: int) -> int:  # n：生成数组的下标上界，返回 nums[0..n] 中的最大值
        if n < 2:  # n 为 0 或 1 时递推式用不上，直接由定义给出答案
            return n  # 返回 n 本身（nums[0]=0、nums[1]=1）
        nums = [0] * (n + 1)  # 初始化长度 n+1 的全 0 数组（下标 0..n）
        nums[1] = 1  # 题目给定 nums[1] = 1
        for i in range(2, n + 1):  # 从下标 2 开始按递推式生成
            nums[i] = nums[i >> 1] if i % 2 == 0 else nums[i >> 1] + nums[(i >> 1) + 1]  # 偶数取 nums[i/2]，奇数取 nums[i/2] + nums[i/2+1]
        return max(nums)  # 扫描整个数组取最大值
