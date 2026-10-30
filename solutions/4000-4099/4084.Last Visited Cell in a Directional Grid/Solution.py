# 题目：4084. 有向网格中的最后访问单元格（Last Visited Cell in a Directional Grid）
# 核心思路：从左上角出发，按当前格子的 L/R/U/D 箭头持续移动，并用 vis 记录走过的格子；当下一步越界或踩到旧格子时停止，返回停下前所在的那一格坐标。
# 时间复杂度：O(m*n)，每个格子最多被访问一次；空间复杂度：O(m*n)，用于访问标记数组。
class Solution:  # LeetCode 约定的题解类
    def lastVisitedCell(self, grid: list[list[str]]) -> list[int]:  # grid：有向网格；返回最后访问的单元格 [行, 列]
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        r = c = 0  # 当前位置从左上角 (0, 0) 开始
        vis = [[False] * n for _ in range(m)]  # vis 记录每个格子是否已被访问
        while 1:  # 不断沿箭头移动，直到无法继续
            cur = [r, c]  # 记下当前坐标，作为可能的最终答案
            vis[r][c] = True  # 标记当前格子已访问
            match grid[r][c]:  # 按当前格子的箭头字符分派下一步移动
                case "L":  # 箭头指向左
                    c -= 1  # 列号减一
                case "R":  # 箭头指向右
                    c += 1  # 列号加一
                case "U":  # 箭头指向上
                    r -= 1  # 行号减一
                case "D":  # 箭头指向下
                    r += 1  # 行号加一
            if 0 <= r < m and 0 <= c < n and not vis[r][c]:  # 下一步未越界且没被访问过，可以继续走
                continue  # 进入下一轮移动
            return cur  # 否则无法继续，返回当前停留的格子
