# 题目：74. 搜索二维矩阵（Search a 2D Matrix）
# 思路：把 m×n 矩阵视为长度为 m*n 的有序一维数组，做「找第一个 >= target 的位置」的下界二分，最后检查该位置是否恰好等于 target。
# 时间复杂度：O(log(m*n))，只做一次二分；空间复杂度：O(1)，只用了常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:  # matrix 是行列均递增的二维矩阵，target 是待查找的目标值
        m, n = len(matrix), len(matrix[0])  # m 是行数，n 是列数，用于一维下标与二维坐标的换算
        left, right = 0, m * n - 1  # 矩阵展平成一维后，二分查找的闭区间是 [left, right]
        while left < right:  # 区间里还剩不止一个元素时继续二分，结束时 left == right 即为候选答案
            mid = (left + right) >> 1  # 取中点，右移一位等价于整除 2 并向下取整
            x, y = divmod(mid, n)  # 把一维下标 mid 一次拆成行号 x 与列号 y（divmod 返回商和余数）
            if matrix[x][y] >= target:  # 中点值不小于目标，首个 >= target 的位置在左半边，且 mid 本身可能是答案
                right = mid  # 保留 mid，把区间收缩成 [left, mid]
            else:  # 中点值小于目标，答案一定落在 mid 的右侧
                left = mid + 1  # 丢弃 mid，把区间收缩成 [mid + 1, right]
        return matrix[left // n][left % n] == target  # 循环结束时 left 是首个 >= target 的位置，判断它是否真的等于 target
