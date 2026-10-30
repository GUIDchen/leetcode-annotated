# 题目：730. 统计不同回文子序列（Count Different Palindromic Subsequences）
# 思路：区间 DP，dp[i][j][c] 表示 s[i..j] 内以字符 c 为首尾的不同回文子序列个数，按区间长度从小到大转移，最后把四种首字符的结果求和。
# 时间复杂度：O(n²·4)，区间数 n² 乘以 4 种字母；空间复杂度：O(n²·4)，即三维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def countPalindromicSubsequences(self, s: str) -> int:  # s 只由 'a'~'d' 组成，因此可以按这 4 种字符分类统计
        mod = 10**9 + 7  # 取模基数 10^9+7
        n = len(s)  # n 为字符串长度
        dp = [[[0] * 4 for _ in range(n)] for _ in range(n)]  # 三维 DP：dp[i][j][k] 表示区间 [i, j] 内以第 k 种字母为首尾的回文子序列数
        for i, c in enumerate(s):  # 枚举每个字符作为区间的退化情形
            dp[i][i][ord(c) - ord('a')] = 1  # 长度为 1 的区间只有一个单字符回文子序列
        for l in range(2, n + 1):  # l 枚举区间长度，从 2 开始（长度 1 已初始化）
            for i in range(n - l + 1):  # i 是左端点，保证右端点 j = i+l-1 不超过 n-1
                j = i + l - 1  # 由左端点与长度推出右端点
                for c in 'abcd':  # c 枚举首尾字符 a~d
                    k = ord(c) - ord('a')  # k 是该字符对应的 DP 下标
                    if s[i] == s[j] == c:  # 两端字符都等于 c：可以用它们各夹一层
                        dp[i][j][k] = 2 + sum(dp[i + 1][j - 1])  # 新增 "cc" 与再套一层共 2 个，加上内部区间全部回文子序列；Python 大整数不溢出，故此处不取模
                    elif s[i] == c:  # 只有左端是 c，右端从区间中去掉
                        dp[i][j][k] = dp[i][j - 1][k]  # 等价于区间 [i, j-1] 的计数
                    elif s[j] == c:  # 只有右端是 c，左端从区间中去掉
                        dp[i][j][k] = dp[i + 1][j][k]  # 等价于区间 [i+1, j] 的计数
                    else:  # 两端都不是 c，收缩到内部区间
                        dp[i][j][k] = dp[i + 1][j - 1][k]  # 沿用 [i+1, j-1] 的计数
        return sum(dp[0][-1]) % mod  # 整串四种首字符的计数求和后统一取模
