# 题目：1727. 重新排列后的最大子矩阵（Largest Submatrix With Rearrangements）
# 思路：先把每格改成向上连续 1 的高度；列可重排，所以把每行降序排序后，前 j 列的最小高度就是 row[j-1]，面积即 j*row[j-1]。
# 时间复杂度：O(m*n*log n)，每行排序；空间复杂度：O(1)，直接在原矩阵上修改。
class Solution:  # LeetCode 约定的题解类
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:  # matrix 是只含 0/1 的矩阵，列可以任意重排
        for i in range(1, len(matrix)):  # 从第二行开始，把每格改成向上的连续 1 的高度
            for j in range(len(matrix[0])):  # 逐列处理
                if matrix[i][j]:  # 只有当前格是 1，才能和上方的连续段接起来
                    matrix[i][j] = matrix[i - 1][j] + 1  # 高度等于上方高度加一
        ans = 0  # 记录最大全 1 子矩阵面积
        for row in matrix:  # 依次把每一行当作子矩阵的底边
            row.sort(reverse=True)  # 降序排序，相当于按高度把列重排到左边
            for j, v in enumerate(row, 1):  # j 是底边宽度，v 是该宽度下的最小高度
                ans = max(ans, j * v)  # 当前宽度能形成的最大面积
        return ans  # 返回最大面积
