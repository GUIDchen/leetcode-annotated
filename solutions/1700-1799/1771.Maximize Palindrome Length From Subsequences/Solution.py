# 题目：1771. 由子序列构造的最长回文串的长度（Maximize Palindrome Length From Subsequences）
# 思路：把两个串拼成 s = word1 + word2，做区间 DP：f[i][j] 表示 s[i..j] 内最长回文子序列的长度；当回文两端分别落在 word1 与 word2 时（i 在 word1 内、j 在 word2 内）才用它更新答案，保证两个串的字符都被用到。
# 时间复杂度：O(n^2)，n = |word1| + |word2|；空间复杂度：O(n^2)，区间 DP 表。
class Solution:  # LeetCode 约定的题解类
    def longestPalindrome(self, word1: str, word2: str) -> int:  # word1、word2 是两个字符串，题目要求回文里两者各至少取一个字符
        s = word1 + word2  # 把两个串拼接起来，回文子序列只要跨越这条分界就是合法答案
        n = len(s)  # 拼接后的长度，也就是 DP 的规模
        f = [[0] * n for _ in range(n)]  # f[i][j] 表示 s[i..j] 内最长回文子序列的长度，初始全为 0
        for i in range(n):  # 枚举长度为 1 的区间
            f[i][i] = 1  # 单个字符本身就是长度 1 的回文
        ans = 0  # ans 记录「两端分别来自 word1 和 word2」的最大回文长度，没有合法答案时为 0
        for i in range(n - 2, -1, -1):  # 区间 DP：i 从右往左枚举
            for j in range(i + 1, n):  # j 从左往右枚举，只处理 i < j 的区间
                if s[i] == s[j]:  # 两端字符相等，就可以同时向回文的两侧扩展
                    f[i][j] = f[i + 1][j - 1] + 2  # 长度 = 去掉两端的内部区间长度 + 2
                    if i < len(word1) <= j:  # 链式比较：i 在 word1 内且 j 在 word2 内，两端恰好各来自一个串
                        ans = max(ans, f[i][j])  # 用它更新最大长度
                else:  # 两端字符不等，回文只能来自去掉左端或去掉右端
                    f[i][j] = max(f[i + 1][j], f[i][j - 1])  # 取两种子区间的较大值
        return ans  # 返回符合要求的最长回文长度（没有合法回文时保持 0）
