# 题目：361. 轰炸敌人（Bomb Enemy）
# 思路：分别对每行、每列做正反两个方向的扫描，用计数 t 统计两堵墙之间的敌人数，累加到矩阵 g，最后在空地上取最大值。
# 时间复杂度：O(mn)，四次遍历网格；空间复杂度：O(mn)，辅助计数矩阵。
class Solution:  # LeetCode 题解类
    def maxKilledEnemies(self, grid: List[List[str]]) -> int:  # grid 是 'W'（墙）、'E'（敌人）、'0'（空地）组成的网格
        m, n = len(grid), len(grid[0])  # 行列数
        g = [[0] * n for _ in range(m)]  # 辅助矩阵：累计每个格子四个方向的敌人数
        for i in range(m):  # 逐行处理水平方向
            t = 0  # 当前行从左往右的连续敌人数
            for j in range(n):  # 从左往右扫描
                if grid[i][j] == 'W':  # 遇到墙
                    t = 0  # 墙阻断视线，计数清零
                elif grid[i][j] == 'E':  # 遇到敌人
                    t += 1  # 计数加一
                g[i][j] += t  # 累加左侧能看到的敌人数
            t = 0  # 重置计数，准备从右往左
            for j in range(n - 1, -1, -1):  # 从右往左扫描
                if grid[i][j] == 'W':  # 遇到墙
                    t = 0  # 墙阻断视线，计数清零
                elif grid[i][j] == 'E':  # 遇到敌人
                    t += 1  # 计数加一
                g[i][j] += t  # 累加右侧能看到的敌人数
        for j in range(n):  # 逐列处理竖直方向
            t = 0  # 当前列从上往下的连续敌人数
            for i in range(m):  # 从上往下扫描
                if grid[i][j] == 'W':  # 遇到墙
                    t = 0  # 墙阻断视线，计数清零
                elif grid[i][j] == 'E':  # 遇到敌人
                    t += 1  # 计数加一
                g[i][j] += t  # 累加上方能看到的敌人数
            t = 0  # 重置计数，准备从下往上
            for i in range(m - 1, -1, -1):  # 从下往上扫描
                if grid[i][j] == 'W':  # 遇到墙
                    t = 0  # 墙阻断视线，计数清零
                elif grid[i][j] == 'E':  # 遇到敌人
                    t += 1  # 计数加一
                g[i][j] += t  # 累加下方能看到的敌人数
        return max(  # 在所有放置点中取最大值
            [g[i][j] for i in range(m) for j in range(n) if grid[i][j] == '0'],  # 生成式只保留值为 '0' 的空地
            default=0,  # 全图没有空地时返回 0
        )  # max 调用结束
