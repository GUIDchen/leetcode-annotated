# 题目：3195. 包含所有 1 的最小矩形面积 I（Find the Minimum Area to Cover All Ones I）
# 思路：扫描矩阵，记录所有 1 的最小行号、最小列号、最大行号、最大列号，这四个值围成的矩形就是最小外接矩形。
# 时间复杂度：O(m·n)，遍历整个矩阵一次；空间复杂度：O(1)，只维护四个边界变量。
class Solution:  # LeetCode 约定的题解类
    def minimumArea(self, grid: List[List[int]]) -> int:  # grid：只含 0/1 的二维矩阵，返回最小矩形面积
        x1 = y1 = inf  # 上、左边界初始化为正无穷，便于取最小值
        x2 = y2 = -inf  # 下、右边界初始化为负无穷，便于取最大值
        for i, row in enumerate(grid):  # 遍历每一行，i 是行号
            for j, x in enumerate(row):  # 遍历该行每一列，j 是列号
                if x == 1:  # 只处理值为 1 的格子
                    x1 = min(x1, i)  # 用当前行号收紧上边界
                    y1 = min(y1, j)  # 用当前列号收紧左边界
                    x2 = max(x2, i)  # 用当前行号收紧下边界
                    y2 = max(y2, j)  # 用当前列号收紧右边界
        return (x2 - x1 + 1) * (y2 - y1 + 1)  # 闭区间长度需加 1，宽乘高即最小面积
