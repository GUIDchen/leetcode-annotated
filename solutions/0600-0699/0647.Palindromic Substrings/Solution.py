# 题目：647. 回文子串（Palindromic Substrings）
# 思路：中心扩展法，枚举全部 2n-1 个回文中心（单字符中心与两字符之间的间隙中心），从每个中心向两侧扩展并统计回文子串个数。
# 时间复杂度：O(n^2)，每个中心最多扩展 O(n) 次；空间复杂度：O(1)，只用到常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def countSubstrings(self, s: str) -> int:  # s 是输入字符串，返回回文子串的个数
        ans, n = 0, len(s)  # ans 计数；n 为字符串长度，供下标边界判断使用
        for k in range(n * 2 - 1):  # 枚举 2n-1 个回文中心
            i, j = k // 2, (k + 1) // 2  # k 为偶数时 i == j（单字符中心），k 为奇数时 i 与 j 相邻（间隙中心）
            while ~i and j < n and s[i] == s[j]:  # ~i 等价于 i != -1，左界未越界、右界未越界且两端字符相等才继续扩
                ans += 1  # 本层又得到一个回文子串
                i, j = i - 1, j + 1  # 左右指针同时向外各挪一位
        return ans  # 返回回文子串总数
