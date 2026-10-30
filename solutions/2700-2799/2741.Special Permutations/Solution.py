# 题目：2741. 特别的排列（Special Permutations）
# 核心思路：状压 DP，f[集合掩码][末尾下标] 表示已选集合、最后一个元素为 nums[j] 的合法排列数，按整除关系转移。
# 时间复杂度：O(2^n * n^2)；空间复杂度：O(2^n * n)。
class Solution:  # LeetCode 约定的题解类
    def specialPerm(self, nums: List[int]) -> int:  # nums：互不相同的正整数数组
        mod = 10**9 + 7  # 结果取模，防止数值过大
        n = len(nums)  # 元素个数
        m = 1 << n  # 状态总数 2^n
        f = [[0] * n for _ in range(m)]  # 二维 DP 表：f[集合掩码][末尾下标]
        for i in range(1, m):  # 枚举所有非空集合
            for j, x in enumerate(nums):  # 同时取得下标 j 与元素值 x
                if i >> j & 1:  # 第 j 位为 1：x = nums[j] 在当前集合中
                    ii = i ^ (1 << j)  # 去掉 j 之后的前缀集合
                    if ii == 0:  # 前缀为空，说明 x 排在第一位
                        f[i][j] = 1  # 只有一个元素的排列方案数为 1
                        continue  # 没有前驱可枚举，跳到下一个状态
                    for k, y in enumerate(nums):  # 枚举前缀集合中的末尾元素 y
                        if x % y == 0 or y % x == 0:  # 相邻两数必须互相整除
                            f[i][j] = (f[i][j] + f[ii][k]) % mod  # 累加合法前缀的方案数并取模
        return sum(f[-1]) % mod  # 全集状态下所有结尾的方案数之和，再取模
