# 题目：3750. 最少翻转次数得到反转二进制字符串（Minimum Number of Flips to Reverse Binary String）
# 核心思路：要让二进制串等于其反转，前后对称的每一位都必须相同；只需逐对比较对称位置，字符不同的那对必须两端各翻转一次，故答案为不同对称对的个数乘 2。
# 复杂度：时间 O(log n)，二进制只有 O(log n) 位；空间 O(log n)，切片会生成一个二进制串。
class Solution:  # LeetCode 约定的题解类
    def minimumFlips(self, n: int) -> int:  # 返回使 n 的二进制串等于其反转所需的最少翻转次数
        s = bin(n)[2:]  # bin(n)[2:] 去掉 '0b' 前缀，得到 n 的二进制串
        m = len(s)  # m 是二进制串的长度
        return sum(s[i] != s[m - i - 1] for i in range(m // 2)) * 2  # 统计前后对称位置字符不同的对数，每对需两端各翻转一次，故乘 2
