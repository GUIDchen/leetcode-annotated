# 题目：1582. 二进制矩阵中的特殊位置（Special Positions in a Binary Matrix）
# 思路：先统计每一行与每一列中 1 的个数，再遍历所有值为 1 的格子，若它所在行与所在列的 1 的个数都恰好为 1，则它是一个特殊位置。
# 时间复杂度：O(m * n)，矩阵被扫描两遍；空间复杂度：O(m + n)，rows 与 cols 两个计数数组。
class Solution:  # LeetCode 约定的题解类
    def numSpecial(self, mat: List[List[int]]) -> int:  # mat 为 0/1 矩阵，返回特殊位置的个数
        rows = [0] * len(mat)  # rows[i] 记录第 i 行中 1 的个数
        cols = [0] * len(mat[0])  # cols[j] 记录第 j 列中 1 的个数
        for i, row in enumerate(mat):  # 遍历每一行及其下标
            for j, x in enumerate(row):  # 遍历行内每个元素及其下标
                rows[i] += x  # 累加到行计数
                cols[j] += x  # 累加到列计数
        ans = 0  # 特殊位置计数
        for i, row in enumerate(mat):  # 第二遍扫描：逐行查找特殊位置
            for j, x in enumerate(row):  # 逐列检查每个格子
                ans += x == 1 and rows[i] == 1 and cols[j] == 1  # 三个条件同时成立时，布尔值 True 会被当作 1 累加
        return ans  # 返回特殊位置的个数
