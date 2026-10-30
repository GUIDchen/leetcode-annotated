# 题目：3286. 穿越网格图的安全路径（Find a Safe Walk Through a Grid）
# 思路：以 grid[i][j] 为进入该格的代价，用 SPFA（双端队列松弛）求起点到终点的最小累计代价，再判断是否严格小于 health。
# 时间复杂度：O(mn)；空间复杂度：O(mn)，用于 dist 表与队列。
class Solution:  # LeetCode 约定的题解类
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:  # grid：0/1 网格（1 表示踩上去消耗 1 点生命值）；health：初始生命值
        m, n = len(grid), len(grid[0])  # 行数与列数
        dist = [[inf] * n for _ in range(m)]  # dist[x][y] 记录走到 (x,y) 的最小累计消耗，先置为无穷大
        dist[0][0] = grid[0][0]  # 起点的格子若是 1 也要先扣血
        q = deque([(0, 0)])  # 双端队列充当 SPFA 队列，起点先入队
        dirs = (-1, 0, 1, 0, -1)  # 四方向增量；pairwise 会把相邻两项两两配成 (dx, dy)
        while q:  # 队列非空说明还有格子可能被松弛
            x, y = q.popleft()  # 弹出队首坐标
            for a, b in pairwise(dirs):  # 枚举上下左右四个方向
                nx, ny = x + a, y + b  # 邻居坐标
                if (  # 判断邻居合法，且经由当前格能得到更小代价
                    0 <= nx < m  # 行下标不越界
                    and 0 <= ny < n  # 列下标不越界
                    and dist[nx][ny] > dist[x][y] + grid[nx][ny]  # 走这条路的累计代价比已知的更小
                ):  # 条件结束
                    dist[nx][ny] = dist[x][y] + grid[nx][ny]  # 松弛：更新邻居的最小累计代价
                    q.append((nx, ny))  # 邻居代价变小，入队继续传播
        return dist[-1][-1] < health  # 终点消耗严格小于 health 才算安全
