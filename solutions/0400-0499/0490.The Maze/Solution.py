# 题目：490. 迷宫（The Maze）
# 思路：把「球能停下的格子」当作图上的节点做 DFS；从某格沿一个方向一路滚到墙前，得到的落点才递归，vis 记录停靠过的格子，最后看终点是否被访问到。
# 时间复杂度：O(m·n)，每个格子至多入栈一次，每次扩展 4 个方向、每方向滚动 O(max(m, n))；空间复杂度：O(m·n)，vis 表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def hasPath(  # 判断球能否从 start 滚到 destination（起点与终点是 [行, 列]）
        self, maze: List[List[int]], start: List[int], destination: List[int]  # 参数续行：maze 是 0/1 迷宫，start 是起点，destination 是终点
    ) -> bool:  # 返回布尔值：能停在终点即 True
        def dfs(i, j):
            if vis[i][j]:  # 已搜索过这个停靠点，直接返回，避免重复与死循环
                return  # 递归出口：什么都不做
            vis[i][j] = True  # 标记本格可以停靠（即从起点可达）
            if [i, j] == destination:  # 已经停在终点，无需再向外扩展，提前剪枝
                return  # 到达终点的分支直接返回
            for a, b in [[0, -1], [0, 1], [1, 0], [-1, 0]]:  # 四个方向的增量：左、右、下、上
                x, y = i, j  # 从当前格出发，沿这个方向一路滚动
                while 0 <= x + a < m and 0 <= y + b < n and maze[x + a][y + b] == 0:  # 只要下一格仍在界内且不是墙，球就会继续滚（遇墙或边界才停）
                    x, y = x + a, y + b  # 两个坐标同时滚进一格
                dfs(x, y)  # 从新的停靠点继续深搜（若原地没动，会因 vis 已标记而立即返回）

        m, n = len(maze), len(maze[0])  # 迷宫行数与列数
        vis = [[False] * n for _ in range(m)]  # 访问表：记录球能停下的格子，初始全部为 False
        dfs(start[0], start[1])  # 从起点开始深搜
        return vis[destination[0]][destination[1]]  # 终点被访问过就说明存在可行路径
