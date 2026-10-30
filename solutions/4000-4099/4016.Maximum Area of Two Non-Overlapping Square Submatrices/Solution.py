# 题目：4016. 两个不重叠子正方形的最大面积（Maximum Area of Two Non-Overlapping Square Submatrices）
# 思路：两个正方形必被一条水平线或竖直线分开。水平情况用两次 DP 分别求出切线上方与下方能放下的最大全 1 正方形边长，取较小值 t 即为两半可同时容纳的边长，面积 t²；竖直情况把矩阵转置后复用同一函数，最后取两种切法的最大面积。
# 时间复杂度：O(m·n)，两次 DP 加一次转置都是线性扫描；空间复杂度：O(m·n)，两张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maxArea(self, mat: list[list[int]]) -> int:  # mat：只含 0/1 的矩阵；返回两个等大且不重叠的全 1 正方形中单个正方形的最大面积
        def calc(mat: list[list[int]]) -> int:  # 内层函数 calc：处理横切（上下两块）的情况
            m, n = len(mat), len(mat[0])  # 矩阵共 m 行 n 列

            f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：以 (i, j) 为左上角的最大全 1 正方形边长（多开一行一列作 0 边界）
            g = [0] * (m + 1)  # g[i]：上边界恰在第 i 行的最大正方形边长
            suf = [0] * (m + 1)  # suf[i]：完全落在第 i..m-1 行内的最大正方形边长
            for i in range(m - 1, 0, -1):  # 自下而上枚举行；i 不取 0，保证切线上方至少留一行
                for j in range(n - 1, -1, -1):  # 自右向左枚举列，靠右侧、下方、右下三个状态递推
                    if mat[i][j]:  # 格子可用才可能成为某个正方形的左上角
                        f[i][j] = min(f[i + 1][j], f[i][j + 1], f[i + 1][j + 1]) + 1  # 三邻居取最小再加 1，即为以 (i, j) 为左上角的最大正方形边长
                        g[i] = max(g[i], f[i][j])  # 更新「上边界在第 i 行」的最大边长
                suf[i] = max(suf[i + 1], g[i])  # 后缀最大值：第 i 行及其下方能放下的最大正方形边长

            f = [[0] * (n + 1) for _ in range(m + 1)]  # 清空 DP 表，改用「右下角」为基准的状态定义
            g = [0] * (m + 1)  # 重置每行的最大边长
            pre = [0] * (m + 1)  # pre[i]：完全落在前 i 行（1-based 的 1..i 行）内的最大正方形边长
            for i in range(1, m + 1):  # 用 1-based 下标自上而下枚举行
                for j in range(1, n + 1):  # 自上而下、自左向右枚举列
                    if mat[i - 1][j - 1]:  # 映射回 0-based 下标，判断格子是否可用
                        f[i][j] = min(f[i - 1][j], f[i][j - 1], f[i - 1][j - 1]) + 1  # 三邻居取最小再加 1，得到以 (i-1, j-1) 为右下角的最大正方形边长
                        g[i] = max(g[i], f[i][j])  # 更新「下边界恰在第 i 行」的最大边长

                pre[i] = max(pre[i - 1], g[i])  # 前缀最大值：前 i 行内能放下的最大正方形边长

            ans = 0  # 答案（单个正方形的面积），找不到两个正方形时保持 0
            for i in range(1, m):  # 枚举水平切线：切在 1-based 第 i 行之后，上方 1..i 行、下方 i+1..m 行
                t = min(pre[i], suf[i])  # 两半都能放下边长 t 的正方形，t 取两半中较小者
                ans = max(ans, t * t)  # 两个正方形等大，单个面积 t²，取全局最大值
            return ans  # 返回该切法下单个正方形的最大面积

        def transpose(mat: list[list[int]]) -> list[list[int]]:  # 内层函数 transpose：转置矩阵，把竖切问题转化为横切问题
            m, n = len(mat), len(mat[0])  # 原矩阵是 m 行 n 列
            ans = [[0] * m for _ in range(n)]  # 转置结果共有 n 行 m 列
            for i in range(m):  # 遍历原矩阵的每一行
                for j in range(n):  # 遍历该行的每一列
                    ans[j][i] = mat[i][j]  # 行列交换：原矩阵的 (i, j) 放到新矩阵的 (j, i)
            return ans  # 返回转置后的矩阵

        return max(calc(mat), calc(transpose(mat)))  # 横切与竖切（转置后等价于横切）两种方案取最优
