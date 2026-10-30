# 题目：2652. 倍数求和（Sum Multiples）
# 思路：枚举 1..n，凡是能被 3、5、7 中任意一个整除的数就累加；一个数同时满足多个条件也只加一次。
# 时间复杂度：O(n)，枚举一次；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def sumOfMultiples(self, n: int) -> int:  # n：统计范围上界（1..n）
        # 用生成器枚举 1..n，只保留能被 3、5、7 整除的数，再由 sum 求和
        # 同一个数同时满足多个整除条件也只出现一次，因此无需去重
        return sum(x for x in range(1, n + 1) if x % 3 == 0 or x % 5 == 0 or x % 7 == 0)  # 返回所有倍数的和
