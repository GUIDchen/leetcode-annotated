# 题目：2204. 无向图中到环的距离（Distance to a Cycle in Undirected Graph）
# 核心思路：拓扑剥离所有度数为 1 的叶子结点，剩下的点构成唯一的环；剥离时记下父结点，最后逆序沿父指针递推距离。
# 时间复杂度：O(n + m)，每个点与每条边只处理常数次；空间复杂度：O(n + m)，邻接表、队列与若干 O(n) 数组。
class Solution:  # LeetCode 约定的题解类
    def distanceToCycle(self, n: int, edges: List[List[int]]) -> List[int]:  # n 是结点数，edges 是无向边列表
        g = defaultdict(set)  # 邻接表：g[v] 是与 v 相邻的结点集合，方便 O(1) 删边
        for a, b in edges:  # 逐条无向边建图
            g[a].add(b)  # 记录 a 的邻居 b
            g[b].add(a)  # 无向图要双向登记
        q = deque(i for i in range(n) if len(g[i]) == 1)  # 把所有度数为 1 的叶子作为剥离起点入队
        f = [0] * n  # f[v] 记录 v 被剥离时唯一的邻居，即树上的父结点
        seq = []  # seq 按剥离顺序保存所有非环节点
        while q:  # 不断剥离叶子，直到队列为空、只剩环
            i = q.popleft()  # 取出队首叶子
            seq.append(i)  # 记录剥离顺序，便于后面逆序递推
            for j in g[i]:  # 遍历叶子 i 当前仅存的邻居
                g[j].remove(i)  # 从 j 的邻接表中删去 i，模拟剥离这条边
                f[i] = j  # i 的父结点是 j，它的距离由 j 推出
                if len(g[j]) == 1:  # j 删边后度数变成 1，成为新的叶子
                    q.append(j)  # 新叶子入队，继续剥离
            g[i].clear()  # 清空 i 的邻接表，标记它已不在图中
        ans = [0] * n  # 环上结点的距离为 0，因此整体初始化为 0 即可
        for i in seq[::-1]:  # 逆序（从环向外）递推距离
            ans[i] = ans[f[i]] + 1  # i 比父结点 f[i] 多走一条边，距离加 1
        return ans  # 返回每个结点到环的距离
