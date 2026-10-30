# 题目：1293. 网格中的最短路径（Shortest Path in a Grid with Obstacles Elimination）
# 核心思路：以「(行, 列, 剩余消除次数)」为状态做逐层 BFS 求最短路；先剪掉 k ≥ m+n-3 时必然可直达的情形。
# 时间复杂度：O(m·n·k)，状态数最多 m·n·(k+1)；空间复杂度：O(m·n·k)，访问标记数组。
class Solution:  # LeetCode 约定的题解类
    def shortestPath(self, grid: List[List[int]], k: int) -> int:  # 题解方法对外可见
        m, n = len(grid), len(grid[0])  # grid 是 0/1 网格，k 是最多可消除的障碍数，返回左上到右下的最短步数
        if k >= m + n - 3:  # m、n 分别是网格的行数与列数
            return m + n - 2  # 剪枝：可消除的障碍数足够多时，最短路径上的障碍都能清掉，直接返回最短步数
        q = deque([(0, 0, k)])  # 队列里放状态 {行, 列, 剩余消除次数}
        vis = {(0, 0, k)}  # 起点入队，初始剩余消除次数为 k
        ans = 0  # vis[i][j][r] 表示「到达 (i,j) 且还剩 r 次消除机会」这个状态是否已被访问
        while q:  # 标记起点状态已访问，防止回头重复入队
            ans += 1  # ans 记录 BFS 的层数，也就是已走的步数
            for _ in range(len(q)):  # 方向数组：相邻两项组成一个方向 (dx, dy)，覆盖上下左右四个方向
                i, j, k = q.popleft()  # 按层 BFS，队列非空就继续
                for a, b in [[0, -1], [0, 1], [1, 0], [-1, 0]]:  # 进入新的一层，步数加一
                    x, y = i + a, j + b  # 只弹出当前层的 size 个状态，保证层序不乱
                    if 0 <= x < m and 0 <= y < n:  # 取出队首状态 {行, 列, 剩余消除次数}
                        if x == m - 1 and y == n - 1:  # 取出该状态剩余的消除次数，覆盖外层变量 k
                            return ans  # 队首出队
                        if grid[x][y] == 0 and (x, y, k) not in vis:  # 枚举四个方向
                            q.append((x, y, k))  # 计算相邻格子的坐标
                            vis.add((x, y, k))  # 判断新坐标是否落在网格内部
                        if grid[x][y] == 1 and k > 0 and (x, y, k - 1) not in vis:  # 走到终点，当前层数就是最短步数，直接返回
                            q.append((x, y, k - 1))  # 空地且该状态未访问过，可以零代价通过
                            vis.add((x, y, k - 1))  # 把新状态入队
        return -1  # 标记新状态已访问
