# 题目：2371. 最小化网格中的最大值（Minimize Maximum Value in a Grid）
# 核心思路：把格子按原值升序排序，依次贪心填入 max(本行已填最大值, 本列已填最大值) + 1，既能保持行列大小关系，又能让整体最大值尽量小。
# 时间复杂度：O(mn log(mn))，排序主导；空间复杂度：O(mn)，排序列表与答案矩阵。
class Solution:  # LeetCode 约定的题解类
    def minScore(self, grid: List[List[int]]) -> List[List[int]]:  # grid：带重复值的非负整数矩阵，返回同形状的新矩阵
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        nums = [(v, i, j) for i, row in enumerate(grid) for j, v in enumerate(row)]  # 把每个格子打包成 (原值, 行号, 列号)，值在第一位所以排序时按值比较
        nums.sort()  # 按原值升序排列，值相同的格子之间再按行列定序，结果依然合法
        row_max = [0] * m  # row_max[i]：第 i 行目前填过的最大值，初始为 0
        col_max = [0] * n  # col_max[j]：第 j 列目前填过的最大值，初始为 0
        ans = [[0] * n for _ in range(m)]  # 答案矩阵，m 行 n 列全部置 0，注意每行要用独立列表避免别名共享
        for _, i, j in nums:  # 按原值从小到大填：轮到我时，比我小的格子都已填好并刷新过行、列最大值
            ans[i][j] = max(row_max[i], col_max[j]) + 1  # 必须同时大于本行与本列已有的最大值，取较大者加一，保持原来的严格大小关系
            row_max[i] = col_max[j] = ans[i][j]  # 填完后同步刷新行最大值与列最大值，供后面更大的格子使用（链式赋值一次写两处）
        return ans  # 所有格子填完，返回构造出的矩阵
