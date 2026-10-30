# 题目：1689. 十-二进制数的最少数目（Partitioning Into Minimum Number Of Deci-Binary Numbers）
# 思路：每个十-二进制数每一位非 0 即 1，数字串中最大的那一位决定了最少需要的数的个数。
# 时间复杂度：O(n)，扫描一遍字符串；空间复杂度：O(1)，只返回一个整数。
class Solution:  # LeetCode 约定的题解类
    def minPartitions(self, n: str) -> int:  # n：十进制数字串
        return int(max(n))  # 字符比较与数值比较一致，最大字符转成整数就是答案
