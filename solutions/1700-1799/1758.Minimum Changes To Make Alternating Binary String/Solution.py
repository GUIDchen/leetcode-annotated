# 题目：1758. 生成交替二进制字符串的最少操作数（Minimum Changes To Make Alternating Binary String）
# 思路：交替串只有 "0101..." 和 "1010..." 两种，统计与 "0101..." 不同的位数 cnt，答案即 min(cnt, n - cnt)。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用计数变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, s: str) -> int:  # s 是给定的二进制字符串
        cnt = sum(c != '01'[i & 1] for i, c in enumerate(s))  # 偶数位期望 '0'、奇数位期望 '1'，统计与 "0101..." 不一致的位数
        return min(cnt, len(s) - cnt)  # 另一种交替模式 "1010..." 的代价是 len(s)-cnt，取两者较小值
