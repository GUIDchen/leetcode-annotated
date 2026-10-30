# 题目：1706. 球会落何处（Where Will the Ball Fall）
# 思路：对每个球做一次向下递归；每层先判断撞墙与两块挡板相对形成的 V/∧ 夹口，没卡住就沿挡板方向进入下一层，走到第 m 层即为出口列。
# 时间复杂度：O(m × n)，每个球最多走 m 层；空间复杂度：O(m)，递归调用栈深度。
class Solution:  # LeetCode 约定的题解类
    def findBall(self, grid: List[List[int]]) -> List[int]:  # grid：n 列挡板网格，1 表示向右下引导、-1 表示向左下引导
        def dfs(i: int, j: int) -> int:  # dfs(i, j)：球位于第 i 层第 j 列，返回最终掉出的列号，卡住则返回 -1
            if i == m:  # 球已经越过最后一层，说明顺利掉出
                return j  # 当前列就是掉出的列号
            if j == 0 and grid[i][j] == -1:  # 在第 0 列且挡板朝左，球被左边墙挡住
                return -1  # 卡住，按题意返回 -1
            if j == n - 1 and grid[i][j] == 1:  # 在最右列且挡板朝右，球被右边墙挡住
                return -1  # 卡住，按题意返回 -1
            if grid[i][j] == 1 and grid[i][j + 1] == -1:  # 当前挡板朝右而右邻挡板朝左，两块板形成 V 形夹口，球落不下去
                return -1  # 球被夹住，返回 -1
            if grid[i][j] == -1 and grid[i][j - 1] == 1:  # 当前挡板朝左而左邻挡板朝右，两块板形成 ∧ 形夹口，球落不下去
                return -1  # 球被夹住，返回 -1
            return dfs(i + 1, j + 1) if grid[i][j] == 1 else dfs(i + 1, j - 1)  # 挡板朝右则下一层列号 +1，朝左则 -1，继续递归

        m, n = len(grid), len(grid[0])  # m 是层数，n 是列数，dfs 通过闭包引用这两个值
        return [dfs(0, j) for j in range(n)]  # 对每个球从顶部各列出发，收集各自的落点
