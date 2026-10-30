# 题目：1463. 摘樱桃 II（Cherry Pickup II）
# 思路：两个机器人按行同步推进，f[i][j1][j2] 表示走到第 i 行、两机器人分别位于 j1、j2 列时的最大收益；每个机器人上一行来自 j-1、j、j+1 三列之一，两机器人同格时樱桃只算一次。
# 时间复杂度：O(m×n^2×9)，每行枚举 n^2 个位置、每个位置 9 种来源组合；空间复杂度：O(m×n^2)，三维 dp 表。
class Solution:  # LeetCode 约定的题解类
    def cherryPickup(self, grid: List[List[int]]) -> int:  # grid：每格樱桃数；返回两机器人合计能摘到的最大樱桃数
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        f = [[[-1] * n for _ in range(n)] for _ in range(m)]  # 三维 dp 表，全部初始化为 -1 表示不可达
        f[0][0][n - 1] = grid[0][0] + grid[0][n - 1]  # 初始状态：一个在左上角、一个在右上角
        for i in range(1, m):  # 从第 1 行开始逐行向下推进
            for j1 in range(n):  # 枚举第一个机器人本行的列
                for j2 in range(n):  # 枚举第二个机器人本行的列
                    x = grid[i][j1] + (0 if j1 == j2 else grid[i][j2])  # 本行收益；两机器人同格时该格樱桃只算一次
                    for y1 in range(j1 - 1, j1 + 2):  # 第一个机器人上一行的三个候选来源列（j1-1、j1、j1+1）
                        for y2 in range(j2 - 1, j2 + 2):  # 第二个机器人上一行的三个候选来源列（j2-1、j2、j2+1）
                            if 0 <= y1 < n and 0 <= y2 < n and f[i - 1][y1][y2] != -1:  # 来源列不能越界，且上一行状态必须可达（不为 -1）
                                f[i][j1][j2] = max(f[i][j1][j2], f[i - 1][y1][y2] + x)  # 用上一行可达状态加本行收益，更新当前状态的最大值
        return max(f[-1][j1][j2] for j1, j2 in product(range(n), range(n)))  # 最后一行所有 (j1, j2) 组合中取最大值作为答案
