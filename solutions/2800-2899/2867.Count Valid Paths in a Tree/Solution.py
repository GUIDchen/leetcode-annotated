# 题目：2867. 统计树中的合法路径数目（Count Valid Paths in a Tree）
# 思路：先筛出素数表；用并查集把所有「两端都非素数」的边连成块。再枚举每个素数节点作为路径上唯一的素数，把它各个非素数邻居块的大小两两配对累加。
# 时间复杂度：O(n α(n) + mx log log mx)，并查集近线性加埃氏筛；空间复杂度：O(n + mx)，邻接表、并查集与素数表。
class UnionFind:  # 并查集：维护所有非素数节点之间的连通块
    def __init__(self, n):  # n 是节点总数，内部使用 0..n-1，编号 0 的槽位实际空着
        self.p = list(range(n))  # 父节点数组：初始每个节点的父节点都是自己
        self.size = [1] * n  # 每个连通块的节点数，初始各自为 1

    def find(self, x):  # 查 x 所在集合的根，同时做路径压缩
        if self.p[x] != x:  # 当前节点还不是根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把沿途节点直接挂到根上
        return self.p[x]  # 返回根节点

    def union(self, a, b):  # 合并 a、b 所在集合，返回是否真的发生了合并
        pa, pb = self.find(a), self.find(b)  # 分别找出两个节点所在集合的根
        if pa == pb:  # 本来就在同一集合里
            return False  # 无需合并，告诉调用方没有变化
        if self.size[pa] > self.size[pb]:  # 按大小合并：把小集合挂到大集合下面
            self.p[pb] = pa  # b 的根改为指向 a 的根
            self.size[pa] += self.size[pb]  # 合并后集合大小累加
        else:  # 否则把 a 挂到 b 下面
            self.p[pa] = pb  # a 的根改为指向 b 的根
            self.size[pb] += self.size[pa]  # 合并后集合大小累加
        return True  # 合并成功


mx = 10**5 + 10  # 节点数上限为 1e5，这里多留 10 个余量
prime = [True] * (mx + 1)  # 素数标记表，先全部当作素数
prime[0] = prime[1] = False  # 0 和 1 都不是素数，单独排除
for i in range(2, mx + 1):  # 从小到大枚举用来筛的素因子
    if prime[i]:  # 只有素数才需要去筛掉它的倍数
        for j in range(i * i, mx + 1, i):  # 从 i*i 开始，把 i 的倍数标记为合数
            prime[j] = False  # j 能被 i 整除，不是素数


class Solution:  # LeetCode 约定的题解类
    def countPaths(self, n: int, edges: List[List[int]]) -> int:  # n 个节点，edges 是 n-1 条无向边
        g = [[] for _ in range(n + 1)]  # 邻接表，节点编号 1..n，故开 n+1 个位置
        uf = UnionFind(n + 1)  # 并查集同样按 1..n 编号，0 号位闲置
        for u, v in edges:  # 逐条处理树上的边
            g[u].append(v)  # 在 u 的邻接表里记录 v
            g[v].append(u)  # 无向图，反方向也要记录
            if prime[u] + prime[v] == 0:  # 两端都不是素数，这条边连接同一个非素数块
                uf.union(u, v)  # 把两个端点合并进同一个集合

        ans = 0  # 累加合法路径数
        for i in range(1, n + 1):  # 枚举路径上唯一的那个素数节点
            if prime[i]:  # 只把素数节点当作路径的枢纽
                t = 0  # 已经统计过的其它非素数块的节点数之和
                for j in g[i]:  # 遍历素数节点 i 的所有邻居
                    if not prime[j]:  # 素数—素数边会带来两个素数，不合法，跳过
                        cnt = uf.size[uf.find(j)]  # j 所在非素数连通块的节点数
                        ans += cnt  # 以 i 为一端、块内任一节点为另一端的路径
                        ans += t * cnt  # 这块与之前统计过的块配对，路径穿过 i
                        t += cnt  # 把这块的节点数并入累计，供后面的块配对
        return ans  # 返回合法路径总数
