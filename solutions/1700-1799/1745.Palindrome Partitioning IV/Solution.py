# 题目：1745. 分割回文串 IV（Palindrome Partitioning IV）
# 思路：先用区间 DP 预处理 f[i][j] 表示子串 s[i..j] 是否回文（首尾相等且内部回文），再枚举两个切点，判断三段是否同时回文。
# 时间复杂度：O(n^2)，预处理与枚举切点都是两层循环；空间复杂度：O(n^2)，回文判定表 f。
class Solution:  # LeetCode 约定的题解类
    def checkPartitioning(self, s: str) -> bool:  # 判断 s 能否切成三个非空回文子串
        n = len(s)  # 字符串长度
        f = [[True] * n for _ in range(n)]  # f[i][j] 表示 s[i..j] 是否回文；先全置 True，因为单字符与空区间天然回文
        for i in range(n - 1, -1, -1):  # 左端点从右往左枚举（步长 -1），保证依赖的 f[i+1][j-1] 已经算好
            for j in range(i + 1, n):  # 右端点从 i+1 开始（单字符情况无需再算）
                f[i][j] = s[i] == s[j] and (i + 1 == j or f[i + 1][j - 1])  # 首尾字符相等，且去掉首尾后仍是回文，才是回文
        for i in range(n - 2):  # 第一个切点：第一段为 s[0..i]，后面至少还要留两个字符
            for j in range(i + 1, n - 1):  # 第二个切点：第二段为 s[i+1..j]，第三段至少留一个字符
                if f[0][i] and f[i + 1][j] and f[j + 1][-1]:  # f[j+1][-1] 即 f[j+1][n-1]；三段同时回文则切法成立
                    return True  # 找到一种可行切法立即返回
        return False  # 枚举完所有切法都不行
