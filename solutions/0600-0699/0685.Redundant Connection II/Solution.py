# 题目：685. 冗余连接 II（Redundant Connection II）
# 思路：先看有没有入度为 2 的节点；有则多余边在它的两条入边中，删较晚那条再验证是否仍成环；没有则用并查集找出成环的边。
# 时间复杂度：O(n α(n))，并查集操作近似常数；空间复杂度：O(n)，入度数组与父数组。
class Solution:  # LeetCode 约定的题解类
    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:  # edges 是按顺序给出的有向边
        def find(x: int) -> int:  # 递归查找根节点，同时做路径压缩
            if p[x] != x:  # 当前节点不是根节点
                p[x] = find(p[x])  # 把父指针直接指向根，压缩查找路径
            return p[x]  # 返回根节点

        n = len(edges)  # 节点数等于边数
        ind = [0] * n  # 入度数组：ind[i] 记录节点 i+1 的入度
        for _, v in edges:  # 遍历所有边，只关心终点
            ind[v - 1] += 1  # 终点 v 的入度加 1
        dup = [i for i, (_, v) in enumerate(edges) if ind[v - 1] == 2]  # 收集所有指向入度为 2 的节点的边下标
        p = list(range(n))  # 并查集父数组，初始时每个节点各自成一个集合
        if dup:  # 情况一：存在入度为 2 的节点
            for i, (u, v) in enumerate(edges):  # 先假设删掉较晚的那条入边 dup[1]
                if i == dup[1]:  # 跳过 dup[1] 这条边
                    continue  # 相当于把它删掉
                pu, pv = find(u - 1), find(v - 1)  # 分别找出起点、终点所在集合的根
                if pu == pv:  # 剩下的边里仍然有环，说明删错了
                    return edges[dup[0]]  # 应该删的是较早的那条入边
                p[pu] = pv  # 合并两个集合
            return edges[dup[1]]  # 删掉 dup[1] 后无环，它就是多出来的边
        for i, (u, v) in enumerate(edges):  # 情况二：没有入度为 2 的节点，多余边一定在环上
            pu, pv = find(u - 1), find(v - 1)  # 分别找出起点、终点所在集合的根
            if pu == pv:  # 两端点已连通，这条边会成环
                return edges[i]  # 它就是多余的边
            p[pu] = pv  # 合并两个集合
