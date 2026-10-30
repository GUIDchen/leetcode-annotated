# 题目：960. 删列造序 III（Delete Columns to Make Sorted III）
# 思路：将保留的列视为下标递增序列，相邻保留列必须在所有行上满足 s[j] <= s[i]，用最长上升子序列 DP 求出最多能保留多少列。
# 时间复杂度：O(m²·n)，m 为列数、n 为字符串个数；空间复杂度：O(m)，DP 数组长度 m。
class Solution:  # LeetCode 约定的题解类
    def minDeletionSize(self, strs: List[str]) -> int:  # strs 是等长字符串列表，返回最少要删除的列数
        n = len(strs[0])  # n：列数，即每个字符串的长度
        f = [1] * n  # f[i]：以第 i 列结尾能保留的最长合法列序列长度，初始为 1（只保留自己）
        for i in range(n):  # 枚举作为结尾的列 i
            for j in range(i):  # 枚举前一列 j，只能从更靠左的列转移过来
                if all(s[j] <= s[i] for s in strs):  # 所有行都满足第 j 列 <= 第 i 列，两列才能相邻保留
                    f[i] = max(f[i], f[j] + 1)  # 接在以前一列 j 结尾的最优序列后面
        return n - max(f)  # 总列数减去最多能保留的列数，就是最少删除列数
