# 题目：3342. 到达最后一个房间的最少时间 II（Find Minimum Time to Reach Last Room II）
# 思路：与 I 同为 Dijkstra，区别是第奇数次移动耗时 2 秒、偶数次耗时 1 秒，移动次数等于曼哈顿距离 i+j，故耗时由 (i+j)%2 决定。
# 时间复杂度：O(nm log(nm))；空间复杂度：O(nm)，用于 dist 与堆。
class Solution:  # LeetCode 约定的题解类
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:  # moveTime[i][j] 是进入房间 (i,j) 的最早时刻，返回到达右下角的最少时间
        n, m = len(moveTime), len(moveTime[0])  # 网格的行数与列数
        dist = [[inf] * m for _ in range(n)]  # dist[i][j] 记录到达 (i,j) 的最早时间，初始为无穷大
        dist[0][0] = 0  # 起点 (0,0) 在 0 时刻就已经在了
        pq = [(0, 0, 0)]  # 小顶堆用一个列表模拟，元素为 (时间, 行, 列)
        dirs = (-1, 0, 1, 0, -1)  # 四方向差分，相邻两项配对成一个方向向量
        while 1:  # 反复取当前最早的状态（题目保证能到达终点，堆不会空）
            d, i, j = heappop(pq)  # 弹出到达时间最小的状态
            if i == n - 1 and j == m - 1:  # 第一次弹出终点，说明已经是它最早能到达的时刻
                return d  # 直接返回该时间即为答案
            if d > dist[i][j]:  # 惰性删除：堆里残留的是该点被更新前的旧时间
                continue  # 旧状态直接丢弃
            for a, b in pairwise(dirs):  # 把方向数组两两配对，得到四个方向的增量
                x, y = i + a, j + b  # 邻居坐标
                if 0 <= x < n and 0 <= y < m:  # 邻居必须落在网格内
                    t = max(moveTime[x][y], dist[i][j]) + (i + j) % 2 + 1  # 先等到邻居开门，再加上本步耗时：(i+j) 为偶数时 1 秒，为奇数时 2 秒
                    if dist[x][y] > t:  # 发现了一条更早到达邻居的路径
                        dist[x][y] = t  # 更新邻居的最早到达时间
                        heappush(pq, (t, x, y))  # 新状态入堆，参与后续扩展
