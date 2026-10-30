# 题目：1312. 让字符串成为回文串的最少插入次数（Minimum Insertion Steps to Make a String Palindrome）
# 核心思路：区间 DP + 记忆化：dfs(i, j) 表示把 s[i..j] 变成回文的最少插入次数；
#           两端相等就同时收缩，否则补一个字符后取两种收缩方式的最小值再加一。
# 时间复杂度：O(n^2)，共 O(n^2) 个区间状态；空间复杂度：O(n^2)，@cache 缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minInsertions(self, s: str) -> int:  # s 是待变成回文的字符串
        @cache  # 记忆化装饰器：同一对 (i, j) 只计算一次
        def dfs(i: int, j: int) -> int:  # 返回把 s[i..j] 变成回文的最少插入次数
            if i >= j:  # 区间为空或只剩一个字符
                return 0  # 已经是回文，无需插入
            if s[i] == s[j]:  # 两端字符相同，可以配对
                return dfs(i + 1, j - 1)  # 同时收缩左右两端，不增加次数
            return 1 + min(dfs(i + 1, j), dfs(i, j - 1))  # 两端不同：补一个字符，取两种收缩方式的较小值

        return dfs(0, len(s) - 1)  # 从整个字符串区间开始求解
