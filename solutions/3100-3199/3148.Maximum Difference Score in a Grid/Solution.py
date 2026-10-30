# 题目：3148. 矩阵中的最大得分（Maximum Difference Score in a Grid）
# 思路：路径只能向右或向下，得分等价于「终点值 - 左上方某个格子的值」；用 f[i][j] 记录左上矩形内的最小值，ans 取 max(x - 该最小值)。
# 时间复杂度：O(mn)，整张矩阵只遍历一次；空间复杂度：O(mn)，保存前缀最小值表 f。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, grid: List[List[int]]) -> int:  # grid：输入矩阵
        f = [[0] * len(grid[0]) for _ in range(len(grid))]  # f[i][j]：以 (i,j) 为右下角的前缀矩形中的最小值
        ans = -inf  # ans：最大得分，初值取负无穷
        for i, row in enumerate(grid):  # 逐行遍历
            for j, x in enumerate(row):  # 逐列遍历，x 是当前格子的值
                mi = inf  # mi：左上方可作为起点的最小格子值（(0,0) 处仍是 inf，表示没有起点）
                if i:  # 上方格子存在
                    mi = min(mi, f[i - 1][j])  # 用上方的前缀最小值更新 mi
                if j:  # 左方格子存在
                    mi = min(mi, f[i][j - 1])  # 用左方的前缀最小值更新 mi
                ans = max(ans, x - mi)  # 当前值减去起点最小值，就是一条合法路径的得分
                f[i][j] = min(x, mi)  # 把当前值并入前缀最小值，供右下方格子使用
        return ans  # 返回最大得分
