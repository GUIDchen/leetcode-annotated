# 题目：2812. 找出最安全路径（Find the Safest Path in a Grid）
# 思路：先从所有小偷格子做多源 BFS，求出每个格子到最近小偷的曼哈顿距离（安全度）；再把格子按安全度从大到小逐个加入并查集，起点与终点第一次连通时的高度就是答案。
# 时间复杂度：O(n^2 log n)，需要对 n^2 个格子排序；空间复杂度：O(n^2)，距离表、排序表与并查集。
class UnionFind:  # 并查集：带路径压缩与按大小合并
    def __init__(self, n):  # 初始化 n 个结点的并查集
        self.p = list(range(n))  # p[x] 是 x 的父结点，p[x] == x 表示 x 是根
        self.size = [1] * n  # size[x] 只在 x 是根时有效，表示该连通块的大小

    def find(self, x):  # 查找 x 的根（顺路做路径压缩）
        if self.p[x] != x:  # x 不是根时递归向上找
            self.p[x] = self.find(self.p[x])  # 把 x 直接挂到根上，压缩路径
        return self.p[x]  # 返回根结点

    def union(self, a, b):  # 合并 a、b 所在的两个集合，返回是否真的合并成功
        pa, pb = self.find(a), self.find(b)  # 分别找到两个元素所在集合的根
        if pa == pb:  # 根相同说明已经在同一个集合里
            return False  # 无需合并，返回 False
        if self.size[pa] > self.size[pb]:  # 按大小合并：把小集合挂到大集合的根下面
            self.p[pb] = pa  # 把 pb 这个根挂到 pa 下
            self.size[pa] += self.size[pb]  # 累加连通块的大小
        else:  # 否则反方向挂
            self.p[pa] = pb  # 把 pa 挂到 pb 下
            self.size[pb] += self.size[pa]  # 同样累加新连通块的大小
        return True  # 报告合并成功


class Solution:  # LeetCode 约定的题解类
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:  # grid：0 表示空地、1 表示小偷；返回起点到终点的最大安全度
        n = len(grid)  # 网格边长 n（n × n 的方阵）
        if grid[0][0] or grid[n - 1][n - 1]:  # 起点或终点本身有小偷，安全度必定为 0
            return 0  # 无法避开小偷，直接返回 0
        q = deque()  # BFS 队列，初始装有所有小偷格子（多源）
        dist = [[inf] * n for _ in range(n)]  # dist[i][j] 为到最近小偷的曼哈顿距离，inf 表示尚未访问
        for i in range(n):  # 逐行扫描
            for j in range(n):  # 逐列扫描
                if grid[i][j]:  # 该格子有小偷，作为 BFS 源点
                    q.append((i, j))  # 入队等待向外扩散
                    dist[i][j] = 0  # 小偷格子的安全度为 0
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：与 pairwise 配合得到四个方向的偏移
        while q:  # 多源 BFS，逐层向外扩散
            i, j = q.popleft()  # 取出队首并解包出行列坐标
            for a, b in pairwise(dirs):  # pairwise 依次给出相邻的两个方向分量 (a, b)
                x, y = i + a, j + b  # 计算相邻格子的坐标
                if 0 <= x < n and 0 <= y < n and dist[x][y] == inf:  # 在网格内且尚未访问过才更新距离
                    dist[x][y] = dist[i][j] + 1  # 距离为当前格子的距离加一
                    q.append((x, y))  # 入队继续向外扩散

        q = ((dist[i][j], i, j) for i in range(n) for j in range(n))  # 生成每个格子的 (安全度, 行, 列)，tuple 比较时安全度优先
        q = sorted(q, reverse=True)  # 按安全度从大到小排序
        uf = UnionFind(n * n)  # 并查集，把二维坐标压成一维编号 i * n + j
        for d, i, j in q:  # 从安全度最高的格子开始逐个加入
            for a, b in pairwise(dirs):  # 枚举四个相邻方向
                x, y = i + a, j + b  # 相邻格子的坐标
                if 0 <= x < n and 0 <= y < n and dist[x][y] >= d:  # 邻居在网格内且安全度不低于 d 才能连通
                    uf.union(i * n + j, x * n + y)  # 合并两个格子所在的集合
            if uf.find(0) == uf.find(n * n - 1):  # 起点与终点连通，说明存在安全度不低于 d 的路径
                return int(d)  # 按安全度从高到低合并，首次连通时的高度就是最大安全度（转回 int）
        return 0  # 兜底返回 0（正常流程会提前返回）
