# 题目：712. 两个字符串的最小ASCII删除和（Minimum ASCII Delete Sum for Two Strings）
# 核心思路：二维区间 DP。f[i][j] 表示让 s1 的前 i 个字符与 s2 的前 j 个字符相等的最小删除代价，字符相同就继承左上角，否则删掉其中一个字符并累加其 ASCII 值。
# 时间复杂度：O(m·n)，状态表每个位置算一次；空间复杂度：O(m·n)，需要保存整张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minimumDeleteSum(self, s1: str, s2: str) -> int:  # s1、s2 是输入字符串，返回使两者相等所需删除字符的最小 ASCII 值之和
        m, n = len(s1), len(s2)  # 两个字符串的长度，用于建立 DP 表
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：让 s1 前 i 个字符与 s2 前 j 个字符相等的最小删除代价
        for i in range(1, m + 1):  # 预处理第 0 列：s2 为空时只能把 s1 全部删掉
            f[i][0] = f[i - 1][0] + ord(s1[i - 1])  # 删掉 s1 的第 i 个字符，代价累加它的 ASCII 值
        for j in range(1, n + 1):  # 预处理第 0 行：s1 为空时只能把 s2 全部删掉
            f[0][j] = f[0][j - 1] + ord(s2[j - 1])  # 删掉 s2 的第 j 个字符，代价累加它的 ASCII 值
        for i in range(1, m + 1):  # 按 s1 的长度逐层递推
            for j in range(1, n + 1):  # 按 s2 的长度逐列递推
                if s1[i - 1] == s2[j - 1]:  # 当前两个字符相同，可以免费匹配
                    f[i][j] = f[i - 1][j - 1]  # 不用删除，直接继承去掉这两个字符后的最优解
                else:  # 字符不同，说明至少有一个要被删掉
                    f[i][j] = min(  # 取「删 s1 当前字符」与「删 s2 当前字符」两种方案的较小代价（参数在下一行续写）
                        f[i - 1][j] + ord(s1[i - 1]), f[i][j - 1] + ord(s2[j - 1])  # 两个候选值：删掉 s1 的当前字符 / 删掉 s2 的当前字符
                    )  # min 调用的右括号
        return f[m][n]  # 两个字符串都处理完毕，f[m][n] 就是最终答案
