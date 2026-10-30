# 题目：4010. 数对的最大强度（Maximize Pair Strength Using GCD）
# 思路：直接枚举所有数对 (i, j)，强度为两数乘积除以 gcd 的平方，边枚举边取最大值；Python 大整数天然不会溢出。
# 时间复杂度：O(n^2 log V)，每对都要求一次 gcd；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxPairStrength(self, nums: list[int]) -> int:  # nums：数对从这里选取；返回所有数对中的最大强度
        n = len(nums)  # n 为数组长度
        ans = 0  # ans 记录当前找到的最大强度
        for i in range(n):  # 枚举数对中的第一个元素
            for j in range(i + 1, n):  # 枚举数对中的第二个元素，只向后取以避免重复
                x = nums[i] * nums[j] // gcd(nums[i], nums[j]) ** 2  # 强度 = 两数乘积整除 gcd 的平方（// 为整数除法）
                ans = max(ans, x)  # 更新最大强度
        return ans  # 返回最大强度
