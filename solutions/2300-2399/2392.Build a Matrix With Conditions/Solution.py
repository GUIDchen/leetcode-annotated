# 题目：2392. 给定条件下构造矩阵（Build a Matrix With Conditions）
# 思路：行、列约束各做一次拓扑排序得到顺序；数字按行序放行、按列序放列，行列条件同时满足。
# 时间复杂度：O(k + m + n)；空间复杂度：O(k + m + n)，邻接表与队列的开销。
class Solution:  # LeetCode 约定的题解类
    def buildMatrix(  # 参数较多，函数签名分三行书写
        self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]  # k 阶矩阵；两组条件分别约束行、列中数字的相对顺序
    ) -> List[List[int]]:  # 返回构造出的 k×k 矩阵
        def f(cond):  # 内部辅助函数：对一组先后约束做拓扑排序
            g = defaultdict(list)  # 邻接表，defaultdict 缺省值为空列表，省去判空
            indeg = [0] * (k + 1)  # 入度数组，节点编号 1..k，下标 0 不使用
            for a, b in cond:  # 每条约束 [a, b] 表示 a 必须排在 b 前面
                g[a].append(b)  # 建一条有向边 a → b
                indeg[b] += 1  # b 多了一个前驱，入度加一
            q = deque([i for i, v in enumerate(indeg[1:], 1) if v == 0])  # 初始队列：所有入度为 0、没有任何前置要求的数字
            res = []  # 记录拓扑序
            while q:  # BFS 直到没有可放节点
                for _ in range(len(q)):  # 按层处理：先固定本层节点数
                    i = q.popleft()  # 取出队首节点
                    res.append(i)  # 把它加入拓扑序
                    for j in g[i]:  # 遍历 i 的所有后继
                        indeg[j] -= 1  # 后继少了一个前驱
                        if indeg[j] == 0:  # 入度归零说明前驱都已放好，现在可以放置
                            q.append(j)  # 入队等待处理
            return None if len(res) != k else res  # 排出的数字不足 k 个说明有环，返回 None

        row = f(rowConditions)  # 行方向的拓扑序：决定每个数字在第几行
        col = f(colConditions)  # 列方向的拓扑序：决定每个数字在第几列
        if row is None or col is None:  # 任一方向有环，则不存在合法矩阵
            return []  # 返回空矩阵表示无解
        ans = [[0] * k for _ in range(k)]  # k×k 零矩阵，未填的位置保持 0
        m = [0] * (k + 1)  # 映射「数字 → 应放的列下标」
        for i, v in enumerate(col):  # 遍历列方向的拓扑序
            m[v] = i  # 数字 v 应放在第 i 列
        for i, v in enumerate(row):  # 遍历行方向的拓扑序，逐行放置数字
            ans[i][m[v]] = v  # 把 v 放在第 i 行、列映射给出的列上
        return ans  # 返回构造出的矩阵
