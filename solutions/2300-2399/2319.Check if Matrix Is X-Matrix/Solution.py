# 题目：2319. 判断矩阵是否是一个 X 矩阵（Check if Matrix Is X-Matrix）
# 核心思路：逐格枚举，两条对角线（i==j 与 i+j==n-1）上的元素必须非 0，其余位置必须为 0，遇到违例立即返回 False。
# 时间复杂度：O(n²)，检查全部格子；空间复杂度：O(1)，只用下标变量。
class Solution:  # LeetCode 约定的题解类
    def checkXMatrix(self, grid: List[List[int]]) -> bool:  # grid：n×n 矩阵；返回它是否是一个 X 矩阵
        for i, row in enumerate(grid):  # enumerate 同时取得行下标 i 与整行 row
            for j, v in enumerate(row):  # 再对行内元素枚举，j 是列下标，v 是元素值
                if i == j or i + j == len(grid) - 1:  # 当前格子在主对角线（i==j）或副对角线（i+j==n-1）上
                    if v == 0:  # 对角线上的元素不能为 0
                        return False  # 为 0 则不满足条件，直接返回 False
                elif v:  # 非对角线上的元素必须为 0，v 非 0 时其布尔值为真
                    return False  # 非对角线出现非 0 值，直接返回 False
        return True  # 所有格子都通过检查，返回 True
