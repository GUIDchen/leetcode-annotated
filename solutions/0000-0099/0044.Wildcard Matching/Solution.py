# 题目：44. 通配符匹配（Wildcard Matching）
# 核心思路：递归 + 记忆化搜索，(i, j) 表示 s 从 i、p 从 j 起能否匹配；'?' 通配任意单字符，'*' 既可匹配空串也可多吃一个 s 的字符。
# 时间复杂度：O(m·n)，每个状态只计算一次；空间复杂度：O(m·n)，缓存加递归栈。
class Solution:  # LeetCode 约定的题解类
    def isMatch(self, s: str, p: str) -> bool:  # s 是待匹配串，p 是含 ? 与 * 的模式串，返回能否完全匹配
        @cache  # 记忆化：同一个 (i, j) 状态只真正计算一次
        def dfs(i: int, j: int) -> bool:  # dfs(i, j)：s 从下标 i、p 从下标 j 开始能否匹配
            if i >= len(s):  # s 已经用完了，只需看 p 剩下的部分能否匹配空串
                return j >= len(p) or (p[j] == "*" and dfs(i, j + 1))  # p 也读完才算成功；否则当前位是 * 可匹配空串，继续往后看
            if j >= len(p):  # s 还有剩余而 p 已用尽，无论怎样都匹配不上
                return False  # 返回不匹配
            if p[j] == "*":  # 遇到 *：可以匹配 0 个字符，也可以多吃一个 s 的字符
                return dfs(i + 1, j) or dfs(i + 1, j + 1) or dfs(i, j + 1)  # 多个分支只要有一个走通就成功
            return (p[j] == "?" or s[i] == p[j]) and dfs(i + 1, j + 1)  # ? 通配任意字符，普通字符要求相等，然后两个串同时后移一位

        return dfs(0, 0)  # 从两个串的开头开始匹配
