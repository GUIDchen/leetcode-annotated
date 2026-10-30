# 题目：378. 有序矩阵中第 K 小的元素（Kth Smallest Element in a Sorted Matrix）
# 思路：在数值范围 [最小值, 最大值] 上二分答案，用「左下角出发」的 O(n) 计数判断 <= mid 的元素是否够 k 个。
# 时间复杂度：O(n log(max - min))；空间复杂度：O(1)，只用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def kthSmallest(self, matrix: List[List[int]], k: int) -> int:  # matrix 每行每列都升序，返回其中第 k 小的元素（按值计数，不按去重）
        def check(matrix, mid, k, n):  # 内部辅助函数：判断矩阵中 <= mid 的元素个数是否 >= k
            count = 0  # 计数器
            i, j = n - 1, 0  # 从左下角出发：向上数值变小，向右数值变大
            while i >= 0 and j < n:  # 走到矩阵外就结束统计
                if matrix[i][j] <= mid:  # 当前元素不大于 mid
                    count += i + 1  # 该列第 0 行到第 i 行都不大于 mid，共有 i + 1 个
                    j += 1  # 这一列统计完，右移到下一列
                else:  # 当前元素大于 mid
                    i -= 1  # 该列第 i 行及以下都更大，上移一行
            return count >= k  # 个数达到 k 说明第 k 小不超过 mid

        n = len(matrix)  # 矩阵边长
        left, right = matrix[0][0], matrix[n - 1][n - 1]  # 答案必落在最小值与最大值之间，作为二分的上下界
        while left < right:  # 在数值范围上二分答案，而不是在元素下标上二分
            mid = (left + right) >> 1  # 数值中点，右移一位等价于除以 2
            if check(matrix, mid, k, n):  # 统计 <= mid 的元素个数是否已经够 k 个
                right = mid  # 够了说明第 k 小的值不超过 mid，收缩右界
            else:  # 不够说明第 k 小的值严格大于 mid
                left = mid + 1  # 左界右移，排除 mid 及以下的无效候选
        return left  # left 收敛到第 k 小的数值
