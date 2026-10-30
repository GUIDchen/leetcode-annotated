# 题目：566. 重塑矩阵（Reshape the Matrix）
# 思路：元素总数不同则原样返回；否则用一个一维下标 i 同时映射新旧坐标，逐元素搬运。
# 时间复杂度：O(m·n)，每个元素搬运一次；空间复杂度：O(r·c)，新建结果矩阵。
class Solution:  # LeetCode 约定的题解类
    def matrixReshape(self, mat: List[List[int]], r: int, c: int) -> List[List[int]]:  # mat 是原矩阵，r、c 是新行列数，返回重塑后的矩阵
        m, n = len(mat), len(mat[0])  # m、n 是原矩阵的行数与列数
        if m * n != r * c:  # 元素总数不相等时无法重塑，直接返回原矩阵
            return mat  # 原样返回原矩阵
        ans = [[0] * c for _ in range(r)]  # 构造 r 行 c 列的零矩阵，作为结果容器
        for i in range(m * n):  # 按行优先的一维下标遍历元素总数 m*n
            ans[i // c][i % c] = mat[i // n][i % n]  # 一维下标映射：新矩阵 (i//c, i%c)，原矩阵 (i//n, i%n)
        return ans  # 返回重塑后的矩阵
