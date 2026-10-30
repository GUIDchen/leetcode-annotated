# 题目：63. 不同路径 II（Unique Paths II）
# 思路：记忆化搜索，dfs(i,j) 返回从 (i,j) 到右下角的路径数；越界或遇障碍返回 0，到达终点返回 1，用 @cache 缓存结果。
# 时间复杂度：O(m*n)，每个状态只算一次；空间复杂度：O(m*n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:  # obstacleGrid：1 是障碍物，0 是空地
        @cache  # 记忆化装饰器：把 (i, j) 的结果缓存起来，避免同一状态被反复搜索
        def dfs(i: int, j: int) -> int:  # 返回从 (i, j) 走到右下角的路径数
            if i >= m or j >= n or obstacleGrid[i][j]:  # 越界（只向右向下走，故不必判负）或该格是障碍物
                return 0  # 走不通，计 0 条路径
            if i == m - 1 and j == n - 1:  # 到达右下角，形成一条完整路径
                return 1  # 计 1 条
            return dfs(i + 1, j) + dfs(i, j + 1)  # 向下与向右两种选择的方案数之和

        m, n = len(obstacleGrid), len(obstacleGrid[0])  # 行数、列数；放在闭包之后定义，dfs 调用时按晚绑定读取
        return dfs(0, 0)  # 从左上角出发统计路径总数（此时 m、n 已就绪）
