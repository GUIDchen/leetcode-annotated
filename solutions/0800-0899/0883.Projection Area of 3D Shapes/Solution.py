# 题目：883. 三维形体投影面积（Projection Area of 3D Shapes）
# 思路：一次遍历同时算三种投影：俯视面积统计高度大于 0 的格子，正视与侧视分别累加每行、每列的最大高度。
# 时间复杂度：O(n²)，遍历整个 n×n 网格；空间复杂度：O(1)，只用生成器逐个产出数值。
class Solution:  # LeetCode 约定的题解类
    def projectionArea(self, grid: List[List[int]]) -> int:  # grid：n×n 的高度矩阵，grid[i][j] 表示该格子上立方体的个数
        xy = sum(v > 0 for row in grid for v in row)  # 俯视面积：高度大于 0 的格子数量
        yz = sum(max(row) for row in grid)  # 正视面积：每一行最大高度之和
        zx = sum(max(col) for col in zip(*grid))  # 侧视面积：zip(*grid) 取转置后，每列最大高度之和
        return xy + yz + zx  # 返回三种投影面积之和
