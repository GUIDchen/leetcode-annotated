# 题目：2577. 在网格图中访问一个格子的最少时间（Minimum Time to Visit a Cell In a Grid）
# 思路：用「最早到达时刻」作为最短路距离跑堆优化 Dijkstra；若邻居尚未开放，就靠相邻格来回抖动消耗偶数秒，补齐时间差。
# 时间复杂度：O(mn log(mn))，每个格子最多入堆常数次；空间复杂度：O(mn)，dist 表与堆都存 O(mn) 个状态。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, grid: List[List[int]]) -> int:  # grid[x][y] 是格子的开放时间，返回到达右下角的最早时刻
        if grid[0][1] > 1 and grid[1][0] > 1:  # 起点右边和下边都要等到时刻 1 之后才开放，第 0 秒无处可去，必定无解
            return -1  # 返回 -1 表示无法到达
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        dist = [[inf] * n for _ in range(m)]  # dist[x][y] 表示到达 (x,y) 的最早时刻，先全部初始化为正无穷
        dist[0][0] = 0  # 起点在第 0 秒到达，无需等待
        q = [(0, 0, 0)]  # 小根堆，元素为 (时刻, 行, 列)，初始只有起点
        dirs = (-1, 0, 1, 0, -1)  # 四个方向的偏移量，后面用 pairwise 把它拆成两两相邻的 (dx, dy)
        while 1:  # 堆里还有状态就继续扩展，命中终点时会在循环内直接返回
            t, i, j = heappop(q)  # 弹出并解包当前时刻最小的状态
            if i == m - 1 and j == n - 1:  # 到达终点，堆序保证此刻的 t 就是最小时间
                return t  # 返回最早到达终点的时刻
            for a, b in pairwise(dirs):  # pairwise 依次产出 (-1,0)、(0,1)、(1,0)、(0,-1)，正好对应上下左右四个方向
                x, y = i + a, j + b  # 算出邻居坐标
                if 0 <= x < m and 0 <= y < n:  # 邻居必须在网格内
                    nt = t + 1  # 走一步只花 1 秒，先假设立刻走过去
                    if nt < grid[x][y]:  # 邻居尚未开放，需要等待
                        nt = grid[x][y] + (grid[x][y] - nt) % 2  # 来回抖动只能消耗偶数秒，用差值的奇偶性补齐到不早于开放时间的最早时刻
                    if nt < dist[x][y]:  # 只有当到达时间更早时才松弛
                        dist[x][y] = nt  # 记录 (x,y) 更早的到达时刻
                        heappush(q, (nt, x, y))  # 把新状态压入小根堆继续扩展
