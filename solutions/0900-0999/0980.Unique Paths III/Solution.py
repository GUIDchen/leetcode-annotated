# 题目：980. 不同路径 III（Unique Paths III）
# 思路：统计空格子总数 cnt，从起点回溯 DFS，visited 集合避免重复经过，走到终点时步数恰好为 cnt+1 才计一条路径。
# 时间复杂度：O(m*n*4^(m*n))，回溯穷举所有简单路径；空间复杂度：O(m*n)，访问集合与递归栈。
class Solution:  # LeetCode 约定的题解类
    def uniquePathsIII(self, grid: List[List[int]]) -> int:  # grid：-1 障碍、1 起点、2 终点、0 必须经过的空格
        def dfs(i: int, j: int, k: int) -> int:  # 内层回溯函数：当前位置 (i, j) 与已走步数 k
            if grid[i][j] == 2:  # 走到终点 2
                return int(k == cnt + 1)  # 步数等于空格数 + 1 才合法，int() 把布尔值转成 0/1
            ans = 0  # 累计从当前格子出发的合法路径数
            for a, b in pairwise(dirs):  # pairwise 把方向元组两两配对，得到四个方向向量
                x, y = i + a, j + b  # 算出相邻格子的坐标
                if 0 <= x < m and 0 <= y < n and (x, y) not in vis and grid[x][y] != -1:  # 在界内、未访问过、且不是障碍才能走
                    vis.add((x, y))  # 把新格子加入已访问集合
                    ans += dfs(x, y, k + 1)  # 递归累加路径数，步数加一
                    vis.remove((x, y))  # 回溯：移出集合，允许其它路径再次经过
            return ans  # 返回当前格子的方案数

        m, n = len(grid), len(grid[0])  # m、n 为网格行数和列数
        start = next((i, j) for i in range(m) for j in range(n) if grid[i][j] == 1)  # next 生成器找出值为 1 的起点坐标
        dirs = (-1, 0, 1, 0, -1)  # 四个方向：上、右、下、左
        cnt = sum(row.count(0) for row in grid)  # 把每行中 0 的个数累加，得到空格总数
        vis = {start}  # 访问集合初始只有起点
        return dfs(*start, 0)  # 解包起点坐标开始回溯，初始步数为 0
