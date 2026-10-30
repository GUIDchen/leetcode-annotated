# 题目：2711. 对角线上不同值的数量差（Difference of Number of Distinct Values on Diagonals）
# 思路：对每个格子分别向左上和右下沿对角线收集值到集合，取两个集合大小之差的绝对值。
# 时间复杂度：O(m·n·(m+n))，每个格子最多扫两条对角线；空间复杂度：O(m·n + min(m,n))，结果矩阵与集合。
class Solution:  # LeetCode 约定的题解类
    def differenceOfDistinctValues(self, grid: List[List[int]]) -> List[List[int]]:  # grid 是输入的二维矩阵
        m, n = len(grid), len(grid[0])  # 行数与列数
        ans = [[0] * n for _ in range(m)]  # 结果矩阵，先全部填 0
        for i in range(m):  # 遍历每一行
            for j in range(n):  # 遍历每一列，处理格子 (i, j)
                x, y = i, j  # 对角线游标，从当前格子出发
                s = set()  # 集合用来统计对角线上不同值的个数
                while x and y:  # 坐标都不为 0 时才能继续往左上走
                    x, y = x - 1, y - 1  # 左上移动一格
                    s.add(grid[x][y])  # 收集该对角线格子的值
                tl = len(s)  # 左上对角线的不同值个数
                x, y = i, j  # 游标重置回当前格子
                s = set()  # 换一个新集合统计右下对角线
                while x + 1 < m and y + 1 < n:  # 还能往右下走时继续循环
                    x, y = x + 1, y + 1  # 右下移动一格
                    s.add(grid[x][y])  # 收集该对角线格子的值
                br = len(s)  # 右下对角线的不同值个数
                ans[i][j] = abs(tl - br)  # 题目要求：左上与右下不同值个数之差的绝对值
        return ans  # 返回填好的结果矩阵
