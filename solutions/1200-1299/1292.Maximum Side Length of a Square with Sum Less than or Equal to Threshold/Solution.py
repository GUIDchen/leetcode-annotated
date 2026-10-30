# 题目：1292. 元素和小于等于阈值的正方形的最大边长（Maximum Side Length of a Square with Sum Less than or Equal to Threshold）
# 核心思路：先用二维前缀和 O(1) 求任意子方阵的和，再对边长二分答案，用前缀和判定是否存在满足条件的方阵。
# 时间复杂度：O(m·n·log min(m,n))，二分 log 层、每层判定 O(m·n)；空间复杂度：O(m·n)，用于二维前缀和。
class Solution:  # LeetCode 约定的题解类
    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:  # mat 是非负矩阵，求元素和 ≤ threshold 的正方形最大边长
        def check(k: int) -> bool:  # 局部函数 check(k)：判断是否存在边长恰为 k、元素和 ≤ threshold 的正方形
            for i in range(m - k + 1):  # 枚举正方形左上角的行下标
                for j in range(n - k + 1):  # 枚举正方形左上角的列下标
                    v = s[i + k][j + k] - s[i][j + k] - s[i + k][j] + s[i][j]  # 二维前缀和 O(1) 求正方形和：右下 - 上方 - 左侧 + 左上角
                    if v <= threshold:  # 正方形和不超过阈值即满足条件
                        return True  # 找到就立刻返回 True，省去后续枚举
            return False  # 所有位置都不满足，返回 False

        m, n = len(mat), len(mat[0])  # m、n 分别是矩阵的行数与列数
        s = [[0] * (n + 1) for _ in range(m + 1)]  # s 是二维前缀和数组，多开一行一列以省去边界判断
        for i, row in enumerate(mat, 1):  # 枚举行下标 i（前缀和下标从 1 开始，故起始值为 1）
            for j, x in enumerate(row, 1):  # 枚举列下标 j（同样从 1 开始）
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x  # 容斥原理：上 + 左 - 重叠的左上 + 当前格子
        l, r = 0, min(m, n)  # 二分答案的左右边界：边长最小取 0，最大不超过矩阵短边
        while l < r:  # 二分查找满足条件的最大边长
            mid = (l + r + 1) >> 1  # mid 取上中位数（+1 配合下面的 l = mid 才能避免死循环）
            if check(mid):  # 边长 mid 可行，说明答案至少为 mid
                l = mid  # 把左边界抬到 mid
            else:  # 否则边长 mid 不可行
                r = mid - 1  # 把右边界收缩到 mid - 1
        return l  # l 即满足条件的最大边长
