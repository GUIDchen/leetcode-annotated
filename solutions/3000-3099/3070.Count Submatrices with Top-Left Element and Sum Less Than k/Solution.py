# 题目：3070. 元素和小于等于 k 的子矩阵的数目（Count Submatrices with Top-Left Element and Sum Less Than k）
# 核心思路：所有候选子矩阵的左上角都被固定为 (0,0)，因此只需用二维前缀和递推，判断每个右下角位置的元素和是否不超过 k。
# 时间复杂度：O(m·n)，每个格子递推一次；空间复杂度：O(m·n)，前缀和表比原矩阵多一行一列。
class Solution:  # LeetCode 约定的题解类
    def countSubmatrices(self, grid: List[List[int]], k: int) -> int:  # grid：非负整数矩阵；k：元素和上界；返回元素和小于等于 k 的、左上角固定在 (0,0) 的子矩阵个数
        s = [[0] * (len(grid[0]) + 1) for _ in range(len(grid) + 1)]  # 二维前缀和表，行列各多开一个，第 0 行与第 0 列全为 0，方便统一处理边界
        ans = 0  # 答案计数器
        for i, row in enumerate(grid, 1):  # 从 1 开始枚举行号 i，与多开的一行对齐；row 是当前行
            for j, x in enumerate(row, 1):  # 从 1 开始枚举列号 j，与多开的一列对齐；x 是当前格的值
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x  # 容斥公式：上方 + 左方 - 左上方 + 当前格，得到左上角 i×j 子矩阵的和
                ans += s[i][j] <= k  # 把布尔值 True/False 当 1/0 直接累加，和不超过 k 就计数加一
        return ans  # 返回满足条件的子矩阵数目
