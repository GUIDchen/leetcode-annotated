# 题目：3128. 直角三角形（Right Triangles）
# 思路：先统计每行、每列中 1 的个数；再把每个 1 当作直角顶点，它与同行的其它 1、同列的其它 1 各连一条边，方案数为 (行数-1)*(列数-1)。
# 时间复杂度：O(m * n)，两次遍历矩阵；空间复杂度：O(m + n)，保存行、列的 1 计数。
class Solution:  # LeetCode 约定的题解类
    def numberOfRightTriangles(self, grid: List[List[int]]) -> int:  # 统计以 1 为直角顶点、两条直角边平行于坐标轴的三角形个数
        rows = [0] * len(grid)  # rows[i]：第 i 行中 1 的个数
        cols = [0] * len(grid[0])  # cols[j]：第 j 列中 1 的个数
        for i, row in enumerate(grid):  # 第一次遍历：同时统计每行、每列的 1 的数量
            for j, x in enumerate(row):  # 遍历当前行的每个格子
                rows[i] += x  # 累加到所在行的计数
                cols[j] += x  # 累加到所在列的计数
        ans = 0  # 答案计数器
        for i, row in enumerate(grid):  # 第二次遍历：把每个 1 都当作直角顶点
            for j, x in enumerate(row):  # 遍历当前行的每个格子
                if x:  # 只有非零（值为 1）的格子才能做直角顶点
                    ans += (rows[i] - 1) * (cols[j] - 1)  # 同行其余 1 的个数 × 同列其余 1 的个数
        return ans  # 返回三角形总数
