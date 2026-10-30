# 题目：3276. 选择矩阵中单元格的最大得分（Select Cells in Grid With Maximum Score）
# 思路：按数值从小到大做状压 DP，f[i][j] 表示只考虑数值 1..i、已占用行集合为 j 时的最大得分，每行最多用一次。
# 时间复杂度：O(V · 2^m · m)，V 为矩阵中的最大数值；空间复杂度：O(V · 2^m)，即 DP 表的规模。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, grid: List[List[int]]) -> int:  # grid：共 m 行的矩阵
        g = defaultdict(set)  # g[x] 记录数值 x 出现在哪些行
        mx = 0  # 矩阵中出现过的最大值，决定 DP 的数值上界
        for i, row in enumerate(grid):  # i 是行号
            for x in row:  # 遍历该行的每个元素
                g[x].add(i)  # 记录数值 x 出现在第 i 行
                mx = max(mx, x)  # 更新出现过的最大值
        m = len(grid)  # 行数，也是状态压缩的位数
        f = [[0] * (1 << m) for _ in range(mx + 1)]  # f[i][j]：只考虑数值 1..i、已占用行集合为 j 时的最大得分
        for i in range(1, mx + 1):  # 按数值从小到大枚举
            for j in range(1 << m):  # 枚举所有可能的已占用行集合
                f[i][j] = f[i - 1][j]  # 不选数值 i，直接继承上一层的答案
                for k in g[i]:  # 尝试把数值 i 放在它出现过的第 k 行
                    if j >> k & 1:  # 第 k 行已被占用，才能撤销它
                        f[i][j] = max(f[i][j], f[i - 1][j ^ 1 << k] + i)  # 撤销第 k 行后再加上本次得分 i
        return f[-1][-1]  # 取最大数值、所有行都被占用状态下的答案
