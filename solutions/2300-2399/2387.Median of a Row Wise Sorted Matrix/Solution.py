# 题目：2387. 行排序矩阵的中位数（Median of a Row Wise Sorted Matrix）🔒
# 思路：二分答案；count(x) 用每行的 bisect_right 统计 ≤ x 的个数，第一个满足 count(x) ≥ 中位序号的值就是中位数。
# 时间复杂度：O(m·log n·log V)，V 为值域大小；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def matrixMedian(self, grid: List[List[int]]) -> int:  # grid：每行升序的 m×n 矩阵
        def count(x):  # 统计整个矩阵中不大于 x 的元素个数
            return sum(bisect_right(row, x) for row in grid)  # 每行有序，bisect_right 直接给出该行 ≤ x 的个数，再按行求和

        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        target = (m * n + 1) >> 1  # 中位数是第 (m*n+1)//2 小的元素（m*n 为奇数）
        return bisect_left(range(10**6 + 1), target, key=count)  # 在取值 0..1e6 上按 count 二分，返回第一个 count ≥ target 的位置
