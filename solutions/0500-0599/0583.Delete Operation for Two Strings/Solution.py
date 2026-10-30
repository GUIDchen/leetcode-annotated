# 题目：583. 两个字符串的删除操作（Delete Operation for Two Strings）
# 核心思路：动态规划，f[i][j] 表示使 word1 前 i 个字符与 word2 前 j 个字符相同所需的最少删除次数。
# 时间复杂度：O(m * n)，双重循环填表；空间复杂度：O(m * n)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minDistance(self, word1: str, word2: str) -> int:  # 返回使两串相同所需的最少删除次数
        m, n = len(word1), len(word2)  # 两个字符串的长度
        f = [[0] * (n + 1) for _ in range(m + 1)]  # DP 表：f[i][j] 对应 word1 前 i 个字符与 word2 前 j 个字符
        for i in range(1, m + 1):  # 初始化第一列：word2 取空前缀
            f[i][0] = i  # 只能把 word1 的这 i 个字符全删掉
        for j in range(1, n + 1):  # 初始化第一行：word1 取空前缀
            f[0][j] = j  # 只能把 word2 的这 j 个字符全删掉
        for i, a in enumerate(word1, 1):  # 枚举 word1 的字符，下标从 1 开始便于对应 DP 表
            for j, b in enumerate(word2, 1):  # 枚举 word2 的字符，下标同样从 1 开始
                if a == b:  # 两字符相同，可直接抵消，不产生删除代价
                    f[i][j] = f[i - 1][j - 1]  # 继承去掉这两个字符后的答案
                else:  # 两字符不同，至少要删掉其中一个
                    f[i][j] = min(f[i - 1][j], f[i][j - 1]) + 1  # 删 word1 末尾或删 word2 末尾，取较优者再加 1
        return f[m][n]  # 答案：两个完整字符串的最少删除次数
