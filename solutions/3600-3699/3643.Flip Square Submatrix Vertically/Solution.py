# 题目：3643. 垂直翻转子矩阵（Flip Square Submatrix Vertically）
# 核心思路：子矩阵是边长为 k 的正方形，垂直翻转即上下镜像；只需遍历上半部分的 k/2 行，把它与下方对称行在同一列上的元素逐个交换即可。
# 复杂度：时间 O(k²)，共处理约 k²/2 对元素；空间 O(1)，原地修改，不计返回值。
class Solution:  # LeetCode 题解类
    def reverseSubmatrix(  # 入口：把以 (x, y) 为左上角、边长 k 的正方形子矩阵垂直翻转
        self, grid: List[List[int]], x: int, y: int, k: int  # grid：矩阵；x、y：子矩阵左上角；k：子矩阵边长
    ) -> List[List[int]]:  # 返回原地修改后的矩阵
        for i in range(x, x + k // 2):  # 只枚举上半部分的 k/2 行
            i2 = x + k - 1 - (i - x)  # 与第 i 行关于子矩阵水平中轴上下对称的行号
            for j in range(y, y + k):  # 遍历子矩阵的每一列
                grid[i][j], grid[i2][j] = grid[i2][j], grid[i][j]  # 交换上下对称位置上的两个元素
        return grid  # 返回翻转后的矩阵
