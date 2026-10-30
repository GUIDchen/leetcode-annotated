# 题目：3954. 区间内的兼容数字之和 I（Sum of Compatible Numbers in Range I）
# 思路：在 [max(1, n-k), n+k] 内逐个枚举 x，若 n & x == 0（二进制上没有重叠的 1）就说明兼容，把 x 累加到答案。
# 复杂度：时间 O(k)，空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def sumOfGoodIntegers(self, n: int, k: int) -> int:  # n 是基准数，k 是允许的差值范围
        ans = 0  # ans 累加所有兼容数字之和
        for x in range(max(1, n - k), n + k + 1):  # 枚举 [max(1, n-k), n+k] 闭区间内的每个数
            if (n & x) == 0:  # 按位与为 0 说明二进制上没有重叠的 1，即兼容
                ans += x  # 兼容就把它累加进答案
        return ans  # 返回区间内所有兼容数字之和
