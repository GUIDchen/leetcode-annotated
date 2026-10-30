# 3607. 电网维护 / Power Grid Maintenance
# 核心思路：用并查集把线缆相连的电站合并成连通块，为每个连通块维护一个有序集合；类型 1 查询输出该电站（已离线则输出块内编号最小的在线电站），类型 2 查询把电站移出集合。
# 复杂度：时间 O((c + e + q)·α(c) + q log c)，空间 O(c)；c 为电站数、e 为线路数、q 为查询数。
class UnionFind:  # 并查集：按大小合并维护连通块
    def __init__(self, n):  # 构造函数：n 个电站各自独立成块
        self.p = list(range(n))  # 父节点初始化为自身下标
        self.size = [1] * n  # 块大小初始都为 1

    def find(self, x):  # 查找所在连通块的根，并做路径压缩
        if self.p[x] != x:  # 当前节点不是根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把当前节点直接挂到根上
        return self.p[x]  # 返回根编号

    def union(self, a, b):  # 合并两个电站所在的连通块
        pa, pb = self.find(a), self.find(b)  # 先分别找到两个块的根
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
    def processQueries(  # 主函数：c 为电站数，connections 为线路，queries 为查询序列
        self, c: int, connections: List[List[int]], queries: List[List[int]]  # 后两个入参：线路列表与查询列表
    ) -> List[int]:  # 返回各次类型 1 查询的答案
        uf = UnionFind(c + 1)  # 电站编号从 1 开始，因此开 c+1 大小
        for u, v in connections:  # 把每条线路连接的两个电站合并
            uf.union(u, v)  # 合并该线路的两端
        st = [SortedList() for _ in range(c + 1)]  # 每个连通块配一个有序列表，存块内在线的电站编号
        for i in range(1, c + 1):  # 电站编号取 1 到 c
            st[uf.find(i)].add(i)  # 把电站放进它所属连通块的有序列表中
        ans = []  # 按顺序收集每次查询的答案
        for a, x in queries:  # 逐条处理查询
            root = uf.find(x)  # 找到该电站当前所在连通块的根
            if a == 1:  # 类型 1：查询维护时应输出的电站编号
                if x in st[root]:  # 该电站本身仍在线
                    ans.append(x)  # 直接输出它自己
                elif len(st[root]):  # 否则若块内还有在线电站
                    ans.append(st[root][0])  # 输出块内在线的编号最小的电站
                else:  # 否则块内已无在线电站
                    ans.append(-1)  # 输出 -1 表示无可用电站
            else:  # 类型 2：该电站离线维护
                st[root].discard(x)  # 把它从所属连通块的有序列表中删除（不存在时静默忽略）
        return ans  # 返回所有类型 1 查询的答案
