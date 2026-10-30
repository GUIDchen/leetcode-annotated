# 题目：72. 编辑距离（Edit Distance）
# 思路：二维 DP，f[i][j] 表示 word1 前 i 个字符转成 word2 前 j 个字符的最少操作数；末字符相同则取 f[i-1][j-1]，否则取删除、插入、替换三者的最小值加一。
# 时间复杂度：O(m·n)，需要填满整张 DP 表；空间复杂度：O(m·n)，状态表大小为 (m+1)×(n+1)。
class Solution:  # LeetCode 约定的题解类
    def minDistance(self, word1: str, word2: str) -> int:  # word1 为源串，word2 为目标串
        m, n = len(word1), len(word2)  # 两个串的长度，即 DP 表的两维规模
        f = [[0] * (n + 1) for _ in range(m + 1)]  # 分配 (m+1)×(n+1) 的表，多出的一行一列表示空前缀
        for j in range(1, n + 1):  # 初始化第一行：源串为空前缀时
            f[0][j] = j  # 只能插入 j 个字符，共 j 次操作
        for i, a in enumerate(word1, 1):  # 从 1 开始枚举源串字符（下标与 DP 含义对齐）
            f[i][0] = i  # 第一列：目标串为空前缀，只能删掉 i 个字符
            for j, b in enumerate(word2, 1):  # 从 1 开始枚举目标串字符
                if a == b:  # 两个前缀的末字符相同
                    f[i][j] = f[i - 1][j - 1]  # 该位无需操作，沿用左上角的最优值
                else:
                    f[i][j] = min(f[i - 1][j], f[i][j - 1], f[i - 1][j - 1]) + 1  # 删除、插入、替换三选一，代价再加 1
        return f[m][n]  # 右下角即整串转换所需的最少操作次数
