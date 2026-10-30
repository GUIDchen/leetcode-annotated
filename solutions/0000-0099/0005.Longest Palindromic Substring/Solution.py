# 题目：5. 最长回文子串（Longest Palindromic Substring）
# 思路：区间 DP，f[i][j] 表示 s[i..j] 是否回文；i 倒序、j 正序枚举，保证内部区间 f[i+1][j-1] 先算好。
# 时间复杂度：O(n^2)，枚举全部区间；空间复杂度：O(n^2)，二维布尔表。
class Solution:  # LeetCode 约定的题解类
    def longestPalindrome(self, s: str) -> str:  # s 为输入字符串，返回其中最长回文子串
        n = len(s)  # 字符串长度
        f = [[True] * n for _ in range(n)]  # 二维 DP 表初值全 True；用列表推导让每行是独立对象，避免别名共享
        k, mx = 0, 1  # k 记录最长回文子串起点，mx 记录长度（单字符至少为 1）
        for i in range(n - 2, -1, -1):  # i 从 n-2 递减到 0，保证 f[i+1][j-1] 已经计算
            for j in range(i + 1, n):  # 右端点从 i+1 开始，只看长度 >= 2 的区间
                f[i][j] = False  # 先假设 s[i..j] 不是回文
                if s[i] == s[j]:  # 首尾字符相同才可能构成回文
                    f[i][j] = f[i + 1][j - 1]  # 回文性取决于内部子区间
                    if f[i][j] and mx < j - i + 1:  # 确认是回文，而且比当前答案更长
                        k, mx = i, j - i + 1  # 同时更新起点与长度
        return s[k : k + mx]  # 按下标区间切片返回答案
