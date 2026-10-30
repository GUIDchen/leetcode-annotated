# 题目：499. 迷宫 III（The Maze III）
# 思路：把「球停下来的位置」当作状态做 BFS，记录每个状态的最短滚动距离与字典序最小的路径；滚到洞就停，最后取距离优先、路径字典序次优的解。
# 时间复杂度：O(m*n*max(m,n))，每个状态最多向四个方向各滚一遍；空间复杂度：O(m*n)，dist 与 path 各占 O(m*n)。
class Solution:  # LeetCode 约定的题解类
    def findShortestWay(  # 方法签名的开始：maze 是迷宫，ball 是起点，hole 是洞
        self, maze: List[List[int]], ball: List[int], hole: List[int]  # 三个参数的类型注解：迷宫、起点坐标、洞坐标
    ) -> str:  # 返回值是字符串，可能是滚动指令序列，也可能是 impossible
        m, n = len(maze), len(maze[0])  # 同时取得行数与列数
        r, c = ball  # 拆出起点坐标
        rh, ch = hole  # 拆出洞的坐标
        q = deque([(r, c)])  # BFS 队列，元素是球的「停靠点」，起点先入队
        dist = [[inf] * n for _ in range(m)]  # 到每个停靠点的最短滚动距离，初始为无穷大
        dist[r][c] = 0  # 起点到自己的距离是 0
        path = [[None] * n for _ in range(m)]  # 到每个停靠点的最小字典序路径，None 表示尚未到达
        path[r][c] = ''  # 起点的路径是空串
        while q:  # 队列非空就继续扩展
            i, j = q.popleft()  # 弹出队首停靠点并拆出坐标
            for a, b, d in [(-1, 0, 'u'), (1, 0, 'd'), (0, -1, 'l'), (0, 1, 'r')]:  # 四个方向：上 u、下 d、左 l、右 r（u<d<l<r 正好是字典序）
                x, y, step = i, j, dist[i][j]  # 从当前停靠点出发，距离继承它的最优距离
                while (  # 滚动条件：下一格不越界
                    0 <= x + a < m  # 且行方向合法
                    and 0 <= y + b < n  # 且列方向合法
                    and maze[x + a][y + b] == 0  # 且下一格是空地
                    and (x != rh or y != ch)  # 且当前还没进洞（进洞后必须停下）
                ):  # 四个条件同时满足才继续滚
                    x, y = x + a, y + b  # 前进一步
                    step += 1  # 滚动距离加一
                if dist[x][y] > step or (  # 距离更短，或距离相同但路径字典序更小才更新
                    dist[x][y] == step and path[i][j] + d < path[x][y]  # 同级比较：拼上本步字母后的路径是否更小
                ):  # 两个更新条件的分组结束
                    dist[x][y] = step  # 更新最短距离
                    path[x][y] = path[i][j] + d  # 记录这条更优的路径
                    if x != rh or y != ch:  # 没进洞才把新停靠点入队
                        q.append((x, y))  # 入队继续搜索
        return path[rh][ch] or 'impossible'  # 洞未被访问过时 path 为 None，按题意返回 impossible
