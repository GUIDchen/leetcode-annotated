# 题目：1458. 两个子序列的最大点积（Max Dot Product of Two Subsequences）
# 思路：动态规划，f[i][j] 表示 nums1 前 i 个与 nums2 前 j 个元素能得到的最大点积；转移为「丢掉 nums1[i-1]」「丢掉 nums2[j-1]」「把这两个元素配成一对」三者取最大，配成一对时前缀点积为负就从 0 重新开始。
# 时间复杂度：O(m×n)，共 m×n 个状态且转移 O(1)；空间复杂度：O(m×n)，需要二维 dp 表。
class Solution:  # LeetCode 约定的题解类
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个输入数组，点积只在非空子序列上计算
        m, n = len(nums1), len(nums2)  # 两个数组的长度
        f = [[-inf] * (n + 1) for _ in range(m + 1)]  # dp 表，-inf 表示该状态尚未选出任何一对元素（必然会被转移覆盖）
        for i, x in enumerate(nums1, 1):  # i 从 1 开始，x 是 nums1 的第 i 个元素
            for j, y in enumerate(nums2, 1):  # j 从 1 开始，y 是 nums2 的第 j 个元素
                v = x * y  # 这一对元素的乘积
                f[i][j] = max(f[i - 1][j], f[i][j - 1], max(0, f[i - 1][j - 1]) + v)  # 跳过 nums1[i-1]、跳过 nums2[j-1]、或者拼上这一对（前缀为负时从 0 开始）三种转移取最大
        return f[m][n]  # 两数组都取满时就是最终答案
