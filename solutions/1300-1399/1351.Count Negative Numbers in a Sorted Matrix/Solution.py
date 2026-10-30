# 题目：1351. 统计有序矩阵中的负数（Count Negative Numbers in a Sorted Matrix）
# 思路：利用行、列同时非递增的性质，从左下角开始阶梯扫描：当前值非负就右移，为负就整列累加 n-j 个后上移一行。
# 时间复杂度：O(m + n)，最多右移 n 次、上移 m 次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countNegatives(self, grid: List[List[int]]) -> int:  # grid 的每一行、每一列都按非递增排序
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        i, j = m - 1, 0  # 从矩阵左下角出发：i 向上走，j 向右走
        ans = 0  # ans 累计负数的个数
        while i >= 0 and j < n:  # 还在矩阵范围内就继续阶梯扫描
            if grid[i][j] >= 0:  # 当前值非负，要找的负数一定在右边
                j += 1  # 右移一列
            else:  # 当前值已经是负数
                ans += n - j  # 列单调性保证这一列从 i 行往上全为负，共 n-j 个，直接累加
                i -= 1  # 上移一行，继续统计上面那些行
        return ans  # 返回负数总数
