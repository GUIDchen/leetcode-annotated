# 题目：2603. 收集树中金币（Collect Coins in a Tree）
# 思路：拓扑剪掉所有不含金币的叶子，再把含金币树的最外两层叶子剥掉，剩余边都必须走，答案 = 剩余边数 × 2。
# 时间复杂度：O(n)，每个节点每条边均摊常数次操作；空间复杂度：O(n)，邻接表与队列。
class Solution:  # LeetCode 约定的题解类
    def collectTheCoins(self, coins: List[int], edges: List[List[int]]) -> int:  # coins：每个节点是否有金币；edges：无向边；返回收集全部金币的最少经过边数
        g = defaultdict(set)  # 邻接表用 set 存邻居，才能 O(1) 删除一条边
        for a, b in edges:  # 逐条边建立双向连接
            g[a].add(b)  # a 的邻居中加入 b
            g[b].add(a)  # b 的邻居中加入 a（无向图）
        n = len(coins)  # 节点总数
        q = deque(i for i in range(n) if len(g[i]) == 1 and coins[i] == 0)  # 初始的无金币叶子（度为 1 且没有金币）入队，它们不可能被走到
        while q:  # 自外向内剪掉所有无金币的叶子
            i = q.popleft()  # 取出队首叶子
            for j in g[i]:  # 枚举它当前的邻居
                g[j].remove(i)  # 从邻居的邻居集合里删掉这条边
                if coins[j] == 0 and len(g[j]) == 1:  # 邻居剪完后也变成无金币叶子
                    q.append(j)  # 同样入队等待剪除
            g[i].clear()  # 清空该叶子，表示节点已删除
        for k in range(2):  # 在剩余树上再剥掉两层叶子（金币到必走边的距离为 2）
            q = [i for i in range(n) if len(g[i]) == 1]  # 先收集当前所有叶子，再统一删除，避免遍历时修改集合
            for i in q:  # 逐个删除本层叶子
                for j in g[i]:  # 枚举叶子的邻居
                    g[j].remove(i)  # 从邻居集合中删除这条边
                g[i].clear()  # 清空叶子自身的邻接集合
        return sum(len(g[a]) > 0 and len(g[b]) > 0 for a, b in edges) * 2  # 两端都仍在剩余树中的边必须走，来回共 2 次，求和后乘 2
