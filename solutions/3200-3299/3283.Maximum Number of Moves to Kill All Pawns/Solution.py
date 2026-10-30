# 3283. 吃掉所有兵需要的最多移动次数（Maximum Number of Moves to Kill All Pawns）
# 核心思路：先对起点和每个兵各做一次 BFS，预处理出马走到棋盘任意格的最短步数；再用状压 DP 记忆化搜索，Alice 回合取最大、Bob 回合取最小，枚举下一个要吃的兵。
# 复杂度：时间 O(n·m² + 2ⁿ·n²)，空间 O(2ⁿ·n)，其中 m = 50 为棋盘边长

class Solution:  # 定义题解类
    def maxMoves(self, kx: int, ky: int, positions: List[List[int]]) -> int:  # 返回在双方都采取最优策略时 Alice 能走的最多步数
        @cache  # 用 cache 装饰器做记忆化
        def dfs(last: int, state: int, k: int) -> int:  # 状态：last 为当前所在位置，state 为剩余兵集合，k 为当前行动方（1 为 Alice，0 为 Bob）
            if state == 0:  # 兵已经全部吃完
                return 0  # 没有剩余的移动步数可走
            if k:  # 当前轮到 Alice
                res = 0  # Alice 想最大化步数，初值取 0
                for i, (x, y) in enumerate(positions):  # 枚举下一个要吃掉的兵
                    if state >> i & 1:  # 该兵还没有被吃掉
                        t = dfs(i, state ^ (1 << i), k ^ 1) + dist[last][x][y]  # 吃掉它：累加马步距离并交换行动方
                        if res < t:  # 取步数更多的方案
                            res = t  # 更新最大值
                return res  # 返回 Alice 回合的最优结果
            else:  # 否则当前轮到 Bob
                res = inf  # Bob 想最小化步数，初值取无穷大
                for i, (x, y) in enumerate(positions):  # 枚举下一个要吃掉的兵
                    if state >> i & 1:  # 该兵还没有被吃掉
                        t = dfs(i, state ^ (1 << i), k ^ 1) + dist[last][x][y]  # 吃掉它：累加马步距离并交换行动方
                        if res > t:  # 取步数更少的方案
                            res = t  # 更新最小值
                return res  # 返回 Bob 回合的最优结果

        n = len(positions)  # 兵的数量
        m = 50  # 棋盘边长固定为 50
        dist = [[[-1] * m for _ in range(m)] for _ in range(n + 1)]  # dist[i][x][y]：第 i 个源到格子 (x, y) 的最短马步数，-1 表示未访问
        dx = [1, 1, 2, 2, -1, -1, -2, -2]  # 马走日的 8 种横向偏移
        dy = [2, -2, 1, -1, 2, -2, 1, -1]  # 马走日的 8 种纵向偏移
        positions.append([kx, ky])  # 把骑士起点追加到列表末尾，其下标正好是 n
        for i, (x, y) in enumerate(positions):  # 对起点和每个兵分别做一次 BFS
            dist[i][x][y] = 0  # 源点到自身的距离为 0
            q = deque([(x, y)])  # BFS 队列，初始只有源点
            step = 0  # step 记录当前层对应的步数
            while q:  # 队列非空就继续按层扩展
                step += 1  # 进入下一层，步数加一
                for _ in range(len(q)):  # 本层结点数固定，只弹出本层的结点
                    x1, y1 = q.popleft()  # 取出队首的格子
                    for j in range(8):  # 枚举马的 8 种走法
                        x2, y2 = x1 + dx[j], y1 + dy[j]  # 走一步之后的新坐标
                        if 0 <= x2 < m and 0 <= y2 < m and dist[i][x2][y2] == -1:  # 新坐标仍在棋盘内，且该格尚未被访问过
                            dist[i][x2][y2] = step  # 记录到达该格的最短马步数
                            q.append((x2, y2))  # 该格入队，等待继续向外扩展

        ans = dfs(n, (1 << n) - 1, 1)  # 从起点（下标 n）、全部兵都还在、Alice 先手开始搜索
        dfs.cache_clear()  # 清空缓存，避免不同测试用例之间互相干扰
        return ans  # 返回答案
