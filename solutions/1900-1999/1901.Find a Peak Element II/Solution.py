# 题目：1901. 寻找峰值 II（Find a Peak Element II）
# 思路：对行号二分。求中间行的最大值，若它小于下一行同列的值就说明峰值在下方，否则在上方（含当前行），区间收缩到一行后取该行最大值即峰值。
# 时间复杂度：O(n log m)，m 为行数、n 为列数；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def findPeakGrid(self, mat: List[List[int]]) -> List[int]:  # mat：二维矩阵，相邻元素互不相等
        l, r = 0, len(mat) - 1  # 对行号二分，区间为 [l, r]
        while l < r:  # 行区间还没收缩到一行
            mid = (l + r) >> 1  # 取中间行
            j = mat[mid].index(max(mat[mid]))  # 求中间行最大值所在的列
            if mat[mid][j] > mat[mid + 1][j]:  # 当前行更高，峰值在上方
                r = mid  # 保留上半部分（含 mid）
            else:  # 下一行更高，峰值在下方
                l = mid + 1  # 丢掉上半部分
        return [l, mat[l].index(max(mat[l]))]  # 最终行的最大值位置就是峰值
