# 题目：1377. T 秒后青蛙的位置（Frog Position After T Seconds）
# 思路：从结点 1 开始按层 BFS，每个结点把概率按可选邻居数平分给未访问的邻居；若在第 t 秒到达 target 且无路可走，就返回该概率，否则为 0。
# 时间复杂度：O(n)，每个结点至多入队一次；空间复杂度：O(n)，邻接表、访问数组与队列。
class Solution:  # LeetCode 约定的题解类
    def frogPosition(  # n 为结点数，edges 为无向边，t 为秒数，target 为目标结点
        self, n: int, edges: List[List[int]], t: int, target: int  # 参数换行书写，避免单行过长
    ) -> float:  # 返回 t 秒后青蛙位于 target 结点的概率
        g = defaultdict(list)  # 邻接表：g[u] 存放结点 u 的所有邻居
        for u, v in edges:  # 逐条边建无向图，每条边正反各连一次
            g[u].append(v)  # 从 u 连到 v
            g[v].append(u)  # 从 v 连到 u
        q = deque([(1, 1.0)])  # 队列元素是 (当前结点, 到达该结点的概率)，初始在结点 1，概率为 1
        vis = [False] * (n + 1)  # 访问标记，长度为 n+1 便于直接用 1..n 下标
        vis[1] = True  # 起点 1 置为已访问
        while q and t >= 0:  # 按层推进，每轮代表一秒；t 减到 -1 或队列为空时停止
            for _ in range(len(q)):  # 只处理当前层的结点，期间新入队的是下一秒的结点
                u, p = q.popleft()  # 取出并弹出队首的结点与概率
                cnt = len(g[u]) - int(u != 1)  # 可选邻居数：根结点 1 没有父结点，其余结点要扣掉回父结点的一条边
                if u == target:  # 已经到达目标结点
                    return p if cnt * t == 0 else 0  # 已无路可走就返回当前概率，否则下一秒必定离开 target，概率为 0
                for v in g[u]:  # 枚举当前结点的邻居
                    if not vis[v]:  # 只沿未访问的方向向下走
                        vis[v] = True  # 标记为已访问
                        q.append((v, p / cnt))  # 以 cnt 分之一的条件概率进入该结点
            t -= 1  # 一秒结束，剩余时间减一
        return 0  # t 秒内没有停在 target 上，概率为 0
