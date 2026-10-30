# 题目：317. 离建筑物最近的距离（Shortest Distance from All Buildings）
# 思路：以每个建筑为源点做一次 BFS，累计每个空地被多少个建筑到达以及距离总和，最后取「所有建筑都能到达」的空地中的最小距离和。
# 时间复杂度：O(B·m·n)，B 为建筑数量，每个建筑做一次 BFS；空间复杂度：O(m·n)，访问集合与两个累计矩阵。
class Solution:  # LeetCode 约定的题解类
    def shortestDistance(self, grid: List[List[int]]) -> int:  # grid：0 表示空地、1 表示建筑、2 表示障碍
        m, n = len(grid), len(grid[0])  # 行数与列数
        q = deque()  # BFS 队列（双端队列）
        total = 0  # 建筑总数，用来判断某块空地是否所有建筑都可达
        cnt = [[0] * n for _ in range(m)]  # cnt[i][j]：能到达 (i,j) 的建筑个数
        dist = [[0] * n for _ in range(m)]  # dist[i][j]：这些建筑到 (i,j) 的距离之和
        for i in range(m):  # 枚举每一行寻找建筑
            for j in range(n):  # 内层枚举每一列
                if grid[i][j] == 1:  # 是建筑，就以它为源点做一次 BFS
                    total += 1  # 建筑数加一
                    q.append((i, j))  # 源点入队
                    d = 0  # 当前 BFS 的层数，也就是距离
                    vis = set()  # 本次 BFS 访问过的格子
                    while q:  # 队列非空就继续扩展
                        d += 1  # 进入下一层，距离加一
                        for _ in range(len(q)):  # 一次只处理本层的 len(q) 个节点
                            r, c = q.popleft()  # 取队头
                            for a, b in [[0, 1], [0, -1], [1, 0], [-1, 0]]:  # 四个方向的偏移
                                x, y = r + a, c + b  # 相邻格子的坐标
                                if (  # 多行条件写在同一对括号里，这里是条件的开始
                                    0 <= x < m  # 行不越界
                                    and 0 <= y < n  # 列不越界
                                    and grid[x][y] == 0  # 只能是空地（1 建筑、2 障碍都不行）
                                    and (x, y) not in vis  # 本次 BFS 没有访问过
                                ):
                                    cnt[x][y] += 1  # 该空地能被当前建筑到达，计数加一
                                    dist[x][y] += d  # 把当前建筑到它的距离累加进去
                                    q.append((x, y))  # 入队，下一层继续扩展
                                    vis.add((x, y))  # 标记已访问，防止重复计数
        ans = inf  # 最小距离和，初始为无穷大
        for i in range(m):  # 枚举所有格子
            for j in range(n):  # 内层枚举每一列
                if grid[i][j] == 0 and cnt[i][j] == total:  # 是空地且所有建筑都能到达
                    ans = min(ans, dist[i][j])  # 更新最小距离和
        return -1 if ans == inf else ans  # 没有任何可行空地时返回 -1
