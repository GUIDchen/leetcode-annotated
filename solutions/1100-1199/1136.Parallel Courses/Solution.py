# 题目：1136. 并行课程（Parallel Courses）
# 思路：Kahn 拓扑排序分层 BFS：入度为 0 的课程可同时修，逐层削掉，层数即学期数。
# 时间复杂度：O(n + m)；空间复杂度：O(n + m)，邻接表与入度数组。
class Solution:  # LeetCode 约定的题解类
    def minimumSemesters(self, n: int, relations: List[List[int]]) -> int:  # n 门课程（编号 1..n），relations 是 [先修课, 后续课] 列表，返回最少学期数，有环返回 -1
        g = defaultdict(list)  # 邻接表：g[u] 存放以 u 为先修课的后继课程（defaultdict 自动建空列表）
        indeg = [0] * n  # 每个节点的入度，初始都为 0
        for prev, nxt in relations:  # 遍历所有先修关系建图
            prev, nxt = prev - 1, nxt - 1  # 课程编号 1..n 转成 0..n-1 的下标
            g[prev].append(nxt)  # 记录有向边 prev -> nxt
            indeg[nxt] += 1  # 后继课程的入度加 1
        q = deque(i for i, v in enumerate(indeg) if v == 0)  # 把所有入度为 0 的课程放进队列，作为第一学期可修的课
        ans = 0  # 已修完的学期数
        while q:  # 每轮循环处理一个学期
            ans += 1  # 学期数加 1
            for _ in range(len(q)):  # 先记下本层节点个数，只处理这一批，避免把新学期课程混进来
                i = q.popleft()  # 取出队首课程
                n -= 1  # 这门课已修完，剩余未修课程数减 1
                for j in g[i]:  # 遍历它的后继课程
                    indeg[j] -= 1  # 先修课少了一门，入度减 1
                    if indeg[j] == 0:  # 入度归 0 说明后继课的先修要求全部满足
                        q.append(j)  # 后继课程入队，等下一学期处理
        return -1 if n else ans  # n 归 0 表示无环且全部修完，返回学期数；否则有环返回 -1
