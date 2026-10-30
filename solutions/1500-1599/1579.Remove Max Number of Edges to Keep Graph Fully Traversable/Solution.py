# 题目：1579. 保证图可完全遍历（Remove Max Number of Edges to Keep Graph Fully Traversable）
# 思路：并查集贪心。先尽量用两人共用的 type 3 边同时连通两棵树（一条边收益双倍），再分别用 type 1 / type 2 边补连通；合并失败的边都是可删除的冗余边。
# 时间复杂度：O(E * α(n))，每条边做常数次并查集操作；空间复杂度：O(n)，两个并查集各存父指针与集合大小。
class UnionFind:  # 并查集，用来维护两个图的连通性
    def __init__(self, n):  # 构造：n 个节点各自独立
        self.p = list(range(n))  # 父指针 0..n-1，每个节点自成一个集合
        self.size = [1] * n  # 按大小合并所需的集合大小数组
        self.cnt = n  # 连通分量计数，初始为 n

    def find(self, x):  # 带路径压缩的查找
        if self.p[x] != x:  # 父指针不等于自己说明还没到根
            self.p[x] = self.find(self.p[x])  # 压缩：把当前节点直接挂到根上
        return self.p[x]  # 返回根

    def union(self, a, b):  # 合并 a、b 所在集合（节点编号从 1 开始），返回是否真的合并
        pa, pb = self.find(a - 1), self.find(b - 1)  # 先求两个根，注意编号是 1 基的，转成 0 基下标
        if pa == pb:  # 根相同表示已经连通，这条边多余
            return False  # 未发生合并
        if self.size[pa] > self.size[pb]:  # 按集合大小决定挂接方向，控制树高
            self.p[pb] = pa  # 小集合挂到大集合下面
            self.size[pa] += self.size[pb]  # 更新大集合的大小
        else:  # 对称情况
            self.p[pa] = pb  # 把小根挂到大根下面
            self.size[pb] += self.size[pa]  # 更新大根的大小
        self.cnt -= 1  # 连通分量减少一个
        return True  # 合并成功


class Solution:  # 题解类
    def maxNumEdgesToRemove(self, n: int, edges: List[List[int]]) -> int:  # n 个节点，edges 中每条边为 [类型, u, v]
        ufa = UnionFind(n)  # Alice 的并查集
        ufb = UnionFind(n)  # Bob 的并查集
        ans = 0  # 可删除的边数
        for t, u, v in edges:  # 第一轮：先处理共用边，一条能同时连通两棵树
            if t == 3:  # 类型 3 表示两人都能走
                if ufa.union(u, v):  # Alice 侧合并成功
                    ufb.union(u, v)  # Bob 侧同步合并，共用边对两边同时生效
                else:  # Alice 侧已连通，说明这条共用边多余
                    ans += 1  # 计入可删除数
        for t, u, v in edges:  # 第二轮：处理各自专用边
            if t == 1:  # 类型 1 是 Alice 专用边
                ans += not ufa.union(u, v)  # 合并失败则这条边多余，not 得到 bool 再与 int 相加
            if t == 2:  # 类型 2 是 Bob 专用边
                ans += not ufb.union(u, v)  # 同理统计 Bob 侧多余的边
        return ans if ufa.cnt == 1 and ufb.cnt == 1 else -1  # 两个图都连通才可行，否则返回 -1
