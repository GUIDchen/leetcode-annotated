# 题目：304. 二维区域和检索 - 矩阵不可变（Range Sum Query 2D - Immutable）
# 思路：预处理二维前缀和，用容斥原理在 O(1) 时间内回答任意子矩阵的元素和。
# 时间复杂度：构造 O(mn)、每次查询 O(1)；空间复杂度：O(mn)，存 (m+1)×(n+1) 的前缀和。
class NumMatrix:  # LeetCode 约定的题解类
    def __init__(self, matrix: List[List[int]]):  # 构造函数：matrix 是输入矩阵
        m, n = len(matrix), len(matrix[0])  # 行数 m 与列数 n
        self.s = [[0] * (n + 1) for _ in range(m + 1)]  # 建 (m+1)×(n+1) 的二维前缀和，首行首列作哨兵 0
        for i, row in enumerate(matrix):  # 逐行枚举，i 为行下标
            for j, v in enumerate(row):  # 逐列枚举，j 为列下标，v 为当前元素
                self.s[i + 1][j + 1] = (  # 容斥：上方 + 左方 - 重复的左上角 + 当前元素
                    self.s[i][j + 1] + self.s[i + 1][j] - self.s[i][j] + v  # 上方与左方的前缀和相加，再减去左上角、加上当前元素
                )  # 赋值语句收尾

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:  # 查询左上 (row1,col1) 到右下 (row2,col2) 的子矩阵和
        return (  # 容斥：大矩形减去上方与左方，再加回被减两次的左上角
            self.s[row2 + 1][col2 + 1]  # 右下角对应的前缀和
            - self.s[row2 + 1][col1]  # 减去上方多出来的部分
            - self.s[row1][col2 + 1]  # 减去左方多出来的部分
            + self.s[row1][col1]  # 加回被减两次的左上角
        )  # 表达式结束，返回子矩阵和


# Your NumMatrix object will be instantiated and called as such:
# obj = NumMatrix(matrix)
# param_1 = obj.sumRegion(row1,col1,row2,col2)
