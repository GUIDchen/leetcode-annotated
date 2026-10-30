# 题目：1424. 对角线遍历 II（Diagonal Traverse II）
# 核心思路：同一条对角线上的元素行号加列号相同，把 (i+j, j, 值) 排序后按序取值即为遍历结果。
# 时间复杂度：O(N log N)，N 为元素总数，排序主导；空间复杂度：O(N)，额外保存排序数组。
class Solution:  # LeetCode 约定的题解类
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:  # nums：各行长度可不同的二维数组
        arr = []  # 收集 (对角线编号 i+j, 列号 j, 元素值)
        for i, row in enumerate(nums):  # 枚举行号 i 与该行内容
            for j, v in enumerate(row):  # 枚举该行的列号 j 与元素值 v
                arr.append((i + j, j, v))  # 同一对角线 i+j 相同，再用列号 j 决定对角线内的先后
        arr.sort()  # 按 (i+j, j) 升序排序：对角线递增，对角线内从下往上
        return [v[2] for v in arr]  # 只取出元素值组成结果数组
