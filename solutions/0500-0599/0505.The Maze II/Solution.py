# 题目：505. 迷宫 II（The Maze II）
# 思路：BFS 求最短路。球一旦朝某方向滚动就一直滚到撞墙，故每次从队首格子枚举四个方向、滚到底，距离更短才更新并入队。
# 时间复杂度：O(m*n*(m+n))，每个格子可能被松弛多次、每次滚动最多 O(m+n) 步；空间复杂度：O(m*n)。
class Solution:  # LeetCode 约定的题解类
    def shortestDistance(  # maze：0 空地 1 墙；start/destination：起点与终点坐标（参数较多，分成多行书写）
        self, maze: List[List[int]], start: List[int], destination: List[int]  # 三个参数：迷宫、起点坐标、终点坐标
    ) -> int:  # 返回从起点滚到终点的最少步数，不可达返回 -1
        m, n = len(maze), len(maze[0])  # 行数 m、列数 n
        dirs = (-1, 0, 1, 0, -1)  # 方向增量序列，用 pairwise 两两配对得到上下左右的 (行增量, 列增量)
        si, sj = start  # 起点坐标
        di, dj = destination  # 终点坐标
        q = deque([(si, sj)])  # BFS 队列，初始只有起点
        dist = [[inf] * n for _ in range(m)]  # dist[i][j] 记录滚到 (i, j) 的最少步数，先全设为无穷大
        dist[si][sj] = 0  # 起点到自己的距离为 0
        while q:  # 队列非空就继续 BFS
            i, j = q.popleft()  # 取出队首格子
            for a, b in pairwise(dirs):  # pairwise 把方向序列两两配对，得到 (行增量, 列增量)
                x, y, k = i, j, dist[i][j]  # 从 (i, j) 出发，k 是滚动过程中的累计步数
                while 0 <= x + a < m and 0 <= y + b < n and maze[x + a][y + b] == 0:  # 下一格在界内且不是墙，就继续朝同一方向滚
                    x, y, k = x + a, y + b, k + 1  # 前进一格，步数加一
                if k < dist[x][y]:  # 只有新路径更短才更新
                    dist[x][y] = k  # 记录更优距离
                    q.append((x, y))  # 该格子变优，入队继续松弛
        return -1 if dist[di][dj] == inf else dist[di][dj]  # 终点仍为无穷大说明不可达（返回 -1），否则返回最短步数
