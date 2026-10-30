# 题目：940. 不同的子序列 II（Distinct Subsequences II）
# 思路：以结尾字母为状态去重，f[c] 表示以 c 结尾的不同子序列数，每读一个字符就令 f[c] = 之前所有 f 之和 + 1。
# 时间复杂度：O(26n)，每字符对长度 26 的列表求和；空间复杂度：O(26)，只需常数级列表。
class Solution:  # LeetCode 约定的题解类
    def distinctSubseqII(self, s: str) -> int:  # s 是输入字符串，返回不同非空子序列个数（模 1e9+7）
        mod = 10**9 + 7  # 取模常量，防止数值过大
        f = [0] * 26  # f[c] 表示以第 c 个字母结尾的不同子序列数量，初始全为 0
        for c in s:  # 逐字符扫描字符串
            f[ord(c) - ord("a")] = (sum(f) + 1) % mod  # 新个数 = 已有全部子序列之和 + 1（单字符子序列），覆盖旧值实现去重
        return sum(f) % mod  # 把所有结尾的计数相加即答案
