# 题目：873. 最长的斐波那契子序列的长度（Length of Longest Fibonacci Subsequence）
# 思路：哈希表记录「值 → 下标」，DP 表 f[i][j] 表示以 arr[i]、arr[j] 结尾的最长斐波那契子序列长度；若前项 arr[i]-arr[j] 存在且下标更小即可转移。
# 时间复杂度：O(n^2)，只枚举下标对；空间复杂度：O(n^2)，DP 表与哈希表。
class Solution:  # LeetCode 约定的题解类
    def lenLongestFibSubseq(self, arr: List[int]) -> int:  # arr 是严格递增的正整数数组，求最长的斐波那契式子序列长度
        n = len(arr)  # n 是数组长度
        f = [[0] * n for _ in range(n)]  # f[i][j]：以 arr[i]、arr[j] 结尾（下标 i < j）的最长斐波那契子序列长度
        d = {x: i for i, x in enumerate(arr)}  # 值到下标的映射，用于 O(1) 判断前一项是否存在并取到它的下标
        for i in range(n):  # 外层枚举作为「后一项」的下标 i
            for j in range(i):  # 内层枚举 i 之前的每一项下标 j
                f[i][j] = 2  # 任意两个不同的数本身可看作长度 2 的斐波那契式序列
        ans = 0  # ans 记录全局最长长度，一个都找不到时返回 0
        for i in range(2, n):  # i 至少从 2 开始，因为长度为 3 的序列至少需要三项
            for j in range(1, i):  # 枚举中间项 arr[j] 的下标 j
                t = arr[i] - arr[j]  # 斐波那契式要求 arr[i] = arr[j] + t，反推出前一项 t
                if t in d and (k := d[t]) < j:  # 海象运算符：t 已存在时取出其下标 k，并要求 k < j 保证下标严格递增
                    f[i][j] = max(f[i][j], f[j][k] + 1)  # 在「以 arr[j]、arr[k] 结尾」的长度基础上再延长一项
                    ans = max(ans, f[i][j])  # 用当前状态更新全局最长长度
        return ans  # 返回最长斐波那契子序列的长度，不存在时返回 0
