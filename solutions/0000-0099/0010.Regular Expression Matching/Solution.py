# 题目：10. 正则表达式匹配（Regular Expression Matching）
# 思路：用 @cache 记忆化的递归，(i, j) 表示 s[i:] 与 p[j:] 能否匹配；遇到 "x*" 时枚举“用 0 次”和“用 1 次后原地继续”。
# 时间复杂度：O(mn)，每个状态只算一次；空间复杂度：O(mn)，缓存表的开销。
class Solution:  # LeetCode 约定的题解类
    def isMatch(self, s: str, p: str) -> bool:  # s 是待匹配串，p 是含 '.' 与 '*' 的模式串
        @cache  # 自动缓存 dfs 的返回值，同一 (i, j) 只真正递归一次
        def dfs(i, j):  # 判断 s[i:] 能否被 p[j:] 匹配
            if j >= n:  # 模式串已用完
                return i == m  # 原串也必须用完才算匹配
            if j + 1 < n and p[j + 1] == '*':  # 当前字符后接 '*'，代表可重复 0 次或多次
                return dfs(i, j + 2) or (
                    i < m and (s[i] == p[j] or p[j] == '.') and dfs(i + 1, j)
                )  # 前一项是“用 0 次”直接跳过 "x*"；后一项是“用 1 次”吃掉一个字符后仍停在 j
            return i < m and (s[i] == p[j] or p[j] == '.') and dfs(i + 1, j + 1)  # 无 '*': 字符相等或模式为 '.'，两串各后移一位

        m, n = len(s), len(p)  # 计算长度；写在 dfs 之后也可以，闭包在真正调用时才解析这两个名字
        return dfs(0, 0)  # 从两个串的开头开始匹配
