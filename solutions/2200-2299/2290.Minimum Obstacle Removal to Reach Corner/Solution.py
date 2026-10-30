# 题目：2290. 到达角落需要移除障碍物的最小数目（Minimum Obstacle Removal to Reach Corner）
# 核心思路：0-1 BFS。空地移动代价为 0 压到队头，障碍移动代价为 1 压到队尾，双端队列保证按代价单调出队，终点首次弹出即最优。
# 时间复杂度：O(mn)，每个格子最多进出队常数次；空间复杂度：O(mn)，队列与访问集合。
class Solution:  # LeetCode 约定的题解类
    def minimumObstacles(self, grid: List[List[int]]) -> int:  # grid：0 是空地、1 是障碍；返回最少需要移除的障碍数
        m, n = len(grid), len(grid[0])  # m：行数；n：列数
        q = deque([(0, 0, 0)])  # 双端队列存 (行, 列, 已移除障碍数)，起点 (0,0) 的代价为 0
        vis = set()  # 用集合记录已处理的格子，避免同一格子被多次扩展
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移，相邻两项组成一个方向向量
        while 1:  # 0-1 BFS 主循环：终点必然在有限步内出队并返回，故写成死循环
            i, j, k = q.popleft()  # 从队头取出当前代价最小的状态
            if i == m - 1 and j == n - 1:  # 到达右下角终点
                return k  # 按代价单调出队，此刻的 k 就是最小移除数
            if (i, j) in vis:  # 该格子已被更优（或相同）代价处理过
                continue  # 跳过这个过期的重复状态
            vis.add((i, j))  # 标记为已处理
            for a, b in pairwise(dirs):  # pairwise 把偏移序列两两配对，依次得到四个方向
                x, y = i + a, j + b  # 邻居的行、列坐标
                if 0 <= x < m and 0 <= y < n:  # 只处理界内的邻居
                    if grid[x][y] == 0:  # 空地，走过去不产生新代价
                        q.appendleft((x, y, k))  # 代价不变的边压到队头，优先处理
                    else:  # 障碍格，需要多移除一个障碍
                        q.append((x, y, k + 1))  # 代价加一的边压到队尾，延后处理
