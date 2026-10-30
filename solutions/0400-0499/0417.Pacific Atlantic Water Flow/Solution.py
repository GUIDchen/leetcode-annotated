# 题目：417. 太平洋大西洋水流问题（Pacific Atlantic Water Flow）
# 思路：反向思考，从两个大洋的边界出发做 BFS，只走向「高度不低于当前格」的邻居；两份可达矩阵的交集就是答案。
# 时间复杂度：O(m * n)，每个格子至多入队一次；空间复杂度：O(m * n)，两份访问矩阵与两个队列。
class Solution:  # LeetCode 约定的题解类
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:  # heights 是高度矩阵，返回同时能流向太平洋和大西洋的所有坐标
        def bfs(q: Deque[Tuple[int, int]], vis: List[List[bool]]) -> None:  # 内部 BFS：q 是队列，vis 是对应大洋的可达矩阵（用闭包读取外层的 m、n、heights、dirs）
            while q:  # 队列非空就继续扩散
                x, y = q.popleft()  # 弹出队首坐标
                for dx, dy in pairwise(dirs):  # 用 pairwise 把方向元组两两配对成 (dx, dy)
                    nx, ny = x + dx, y + dy  # 计算邻居坐标
                    if (  # 以下四个条件必须同时满足
                        0 <= nx < m  # 行下标不越界
                        and 0 <= ny < n  # 列下标不越界
                        and not vis[nx][ny]  # 邻居还没被访问过
                        and heights[nx][ny] >= heights[x][y]  # 邻居高度不低于当前格（反向看：水能从邻居流到当前格）
                    ):  # if 条件结束
                        vis[nx][ny] = True  # 标记邻居可从该大洋到达
                        q.append((nx, ny))  # 邻居入队，继续往外扩散

        m, n = len(heights), len(heights[0])  # m 行、n 列
        vis1 = [[False] * n for _ in range(m)]  # 太平洋可达矩阵，初始全 False
        vis2 = [[False] * n for _ in range(m)]  # 大西洋可达矩阵，初始全 False
        q1: Deque[Tuple[int, int]] = deque()  # 太平洋 BFS 队列（左边界与上边界是入口）
        q2: Deque[Tuple[int, int]] = deque()  # 大西洋 BFS 队列（右边界与下边界是入口）
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：相邻两个数组成一个方向

        for i in range(m):  # 把最左列与最右列作为种子
            q1.append((i, 0))  # 最左列入太平洋队列
            vis1[i][0] = True  # 标记最左列已访问
            q2.append((i, n - 1))  # 最右列入大西洋队列
            vis2[i][n - 1] = True  # 标记最右列已访问

        for j in range(n):  # 把最上行与最下行作为种子
            q1.append((0, j))  # 最上行入太平洋队列
            vis1[0][j] = True  # 标记最上行已访问
            q2.append((m - 1, j))  # 最下行入大西洋队列
            vis2[m - 1][j] = True  # 标记最下行已访问

        bfs(q1, vis1)  # 先从太平洋边界进行反向 BFS
        bfs(q2, vis2)  # 再从大西洋边界进行反向 BFS

        return [[i, j] for i in range(m) for j in range(n) if vis1[i][j] and vis2[i][j]]  # 用列表推导收集两个矩阵都为 True 的坐标
