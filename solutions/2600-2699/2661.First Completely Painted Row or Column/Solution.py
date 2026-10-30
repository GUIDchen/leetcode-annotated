# 题目：2661. 找出叠涂元素（First Completely Painted Row or Column）
# 核心思路：先建「值 → 坐标」字典，再按 arr 顺序逐格涂色，用 row/col 计数数组统计每行每列已涂格数，首次满行或满列就返回下标。
# 时间复杂度：O(m*n)，建索引与涂色各线性一次；空间复杂度：O(m*n)，字典与计数数组。
class Solution:  # LeetCode 约定的题解类
    def firstCompleteIndex(self, arr: List[int], mat: List[List[int]]) -> int:  # arr：涂色顺序；mat：待涂色的 m×n 矩阵
        m, n = len(mat), len(mat[0])  # 矩阵的行数 m 与列数 n
        idx = {}  # 字典：值 → 它在矩阵中的（行，列）坐标
        for i in range(m):  # 遍历每一行
            for j in range(n):  # 遍历当前行的每一列
                idx[mat[i][j]] = (i, j)  # 记录该数值的位置，后面就能 O(1) 查到坐标
        row = [0] * m  # row[i]：第 i 行已涂的格数
        col = [0] * n  # col[j]：第 j 列已涂的格数
        for k in range(len(arr)):  # 按涂色顺序推进，k 是当前涂的是第几格
            i, j = idx[arr[k]]  # 取出本次被涂的值所在的行列
            row[i] += 1  # 该行已涂格数加一
            col[j] += 1  # 该列已涂格数加一
            if row[i] == n or col[j] == m:  # 某行涂满 n 格或某列涂满 m 格，说明出现第一条完整的行或列
                return k  # 返回触发“完整行/列”的涂色下标 k
