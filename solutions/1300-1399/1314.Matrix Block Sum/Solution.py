# 题目：1314. 矩阵区域和（Matrix Block Sum）
# 思路：先构造二维前缀和数组，再用容斥原理 O(1) 求出每个位置 k 邻域矩形的元素和。
# 时间复杂度：O(m·n)；空间复杂度：O(m·n)，前缀和数组与答案矩阵各占一份。
class Solution:  # LeetCode 约定的题解类
    def matrixBlockSum(self, mat: List[List[int]], k: int) -> List[List[int]]:  # 方法签名：mat 为输入矩阵，k 为邻域半径
        m, n = len(mat), len(mat[0])  # 分别取矩阵的行数 m 与列数 n
        s = [[0] * (n + 1) for _ in range(m + 1)]  # 前缀和数组，多开一行一列，s[i][j] 表示 mat 前 i 行前 j 列之和
        for i, row in enumerate(mat, 1):  # 从 1 开始枚举行，下标直接与前缀和的偏移对齐
            for j, x in enumerate(row, 1):  # 从 1 开始枚举列，x 为当前元素
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x  # 递推式：上 + 左 - 左上 + 当前格，减去被重复计算的左上部分
        ans = [[0] * n for _ in range(m)]  # 答案矩阵，尺寸与 mat 相同
        for i in range(m):  # 枚举答案的每一行
            for j in range(n):  # 枚举答案的每一列
                x1, y1 = max(i - k, 0), max(j - k, 0)  # 邻域上、左边界，越界处夹到 0
                x2, y2 = min(m - 1, i + k), min(n - 1, j + k)  # 邻域下、右边界，越界处夹到边界下标
                ans[i][j] = (  # 用容斥求矩形和，括号内分两行书写以保持可读性
                    s[x2 + 1][y2 + 1] - s[x1][y2 + 1] - s[x2 + 1][y1] + s[x1][y1]  # 四角加减：右下 - 右上 - 左下 + 左上
                )  # 右括号：下标整体 +1 对应前缀和的偏移
        return ans  # 返回每个位置 k 邻域内元素之和
