# 3608. 包含 K 个连通分量需要的最小时间 / Minimum Time for K Connected Components
# 核心思路：把边按时间升序排序后从末尾反向遍历，用并查集逐条“加入”边；连通分量数首次降到 k 以下时，当前边的时间就是答案。
# 复杂度：时间 O(e log e)（排序主导），空间 O(n)；e 为边数、n 为节点数。
class UnionFind:  # 并查集：按大小合并维护连通块
    def __init__(self, n):  # 构造函数：n 个节点各自独立成块
        self.p = list(range(n))  # 父节点初始化为自身下标
        self.size = [1] * n  # 块大小初始都为 1

    def find(self, x):  # 查找所在连通块的根，并做路径压缩
        if self.p[x] != x:  # 当前节点不是根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把当前节点直接挂到根上
        return self.p[x]  # 返回根编号

    def union(self, a, b):  # 合并两个节点所在的连通块
        pa, pb = self.find(a), self.find(b)  # 先分别找到两个节点的根
        if pa == pb:  # 本来就在同一块里，无需合并
            return False  # 返回合并失败
        if self.size[pa] > self.size[pb]:  # 把较小的块挂到较大的块下面
            self.p[pb] = pa  # 小编号块指向大编号块
            self.size[pa] += self.size[pb]  # 合并后更新大块的规模
        else:  # 否则反过来挂
            self.p[pa] = pb  # 大编号块指向小编号块
            self.size[pb] += self.size[pa]  # 合并后更新大块的规模
        return True  # 返回合并成功


class Solution:  # 题解类
    def minTime(self, n: int, edges: List[List[int]], k: int) -> int:  # 主函数：n 个节点、edges 为带权边、k 为目标连通分量数
        edges.sort(key=lambda x: x[2])  # 按边的权重升序排序
        uf = UnionFind(n)  # 初始化并查集，每个节点自成一个分量
        cnt = n  # 当前连通分量数等于节点数
        for u, v, t in edges[::-1]:  # 从权重最大的边开始反向遍历
            if uf.union(u, v):  # 只有真正合并了两个分量才算有效连接
                cnt -= 1  # 连通分量数减一
                if cnt < k:  # 分量数首次小于 k
                    return t  # 当前边的时间即为最小时间
        return 0  # 所有边都加入后仍不满足，说明不需要任何操作
