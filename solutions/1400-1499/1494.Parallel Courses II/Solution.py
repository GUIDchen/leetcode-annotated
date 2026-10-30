# 题目：1494. 并行课程 II（Parallel Courses II）
# 思路：用位掩码表示已修课程集合，在该状态图上做 BFS；每学期从可修课程中选不超过 k 门，超过时枚举大小为 k 的子集。
# 时间复杂度：O(n·2^n + 3^n)；空间复杂度：O(2^n)，访问集合与队列。
class Solution:  # LeetCode 约定的题解类
    def minNumberOfSemesters(self, n: int, relations: List[List[int]], k: int) -> int:  # 返回修完全部 n 门课所需的最少学期数
        d = [0] * (n + 1)  # d[i] 表示修课程 i 之前必须先修完的课程集合（位掩码）
        for x, y in relations:  # 遍历每条先修关系
            d[y] |= 1 << x  # 课程 y 依赖课程 x，把 x 对应的位置 1
        q = deque([(0, 0)])  # BFS 队列元素为 (已修课程掩码, 已用学期数)
        vis = {0}  # 已访问状态集合，初始只有空集
        while q:  # 队列非空就继续搜索
            cur, t = q.popleft()  # 取出队首状态
            if cur == (1 << (n + 1)) - 2:  # 目标：第 1..n 位全为 1（第 0 位不用，所以减 2）
                return t  # 全部修完，返回学期数
            nxt = 0  # 本学期可修的课程掩码
            for i in range(1, n + 1):  # 逐门检查课程
                if (cur & d[i]) == d[i]:  # 该课程的所有先修课都已修完
                    nxt |= 1 << i  # 加入可修集合
            nxt ^= cur  # 去掉已经修过的位，得到尚未修的可修课程
            if nxt.bit_count() <= k:  # 数量不超过一学期容量，可以一次全修
                if (nxt | cur) not in vis:  # 新状态未访问过
                    vis.add(nxt | cur)  # 标记访问
                    q.append((nxt | cur, t + 1))  # 学期数加一入队
            else:  # 超过容量，需要枚举大小为 k 的子集
                x = nxt  # 保存候选集合
                while nxt:  # 枚举 x 的所有非空子集
                    if nxt.bit_count() == k and (nxt | cur) not in vis:  # 子集大小恰为 k 且状态未访问
                        vis.add(nxt | cur)  # 标记访问
                        q.append((nxt | cur, t + 1))  # 学期数加一入队
                    nxt = (nxt - 1) & x  # 子集枚举：得到下一个更小的子集
