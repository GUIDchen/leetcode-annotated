# 题目：664. 奇怪的打印机（Strange Printer）
# 思路：区间 DP。f[i][j] 是打印 s[i..j] 的最少次数；首尾相同可复用上一次打印，不同则枚举分割点合并子区间。
# 时间复杂度：O(n^3)，三层循环；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def strangePrinter(self, s: str) -> int:  # s 是目标字符串，返回最少打印次数
        n = len(s)  # 字符串长度
        f = [[inf] * n for _ in range(n)]  # f[i][j] 记录打印 s[i..j] 的最少次数，inf（浮点无穷大）作为初值
        for i in range(n - 1, -1, -1):  # 左端点从右往左枚举，保证更短的子区间已经算好
            f[i][i] = 1  # 单个字符打印一次即可
            for j in range(i + 1, n):  # 右端点从小到大枚举
                if s[i] == s[j]:  # 首尾字符相同：打印 s[i..j-1] 时最右字符能一并带出
                    f[i][j] = f[i][j - 1]  # 次数等于 s[i..j-1] 的次数，不用多加一次
                else:  # 首尾不同，必须拆成两段
                    for k in range(i, j):  # 枚举分割点 k
                        f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j])  # 取各分割方案中的最小值
        return f[0][-1]  # f[0][-1] 就是整个字符串的答案并返回
