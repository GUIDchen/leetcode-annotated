# 题目：684. 冗余连接（Redundant Connection）
# 思路：并查集按顺序处理每条边，若两端点已在同一集合中，这条边会造成环，它就是答案。
# 时间复杂度：O(n α(n))，并查集单次操作近似常数；空间复杂度：O(n)，父数组。
class Solution:  # LeetCode 约定的题解类
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:  # edges 是按顺序给出的边
        def find(x: int) -> int:  # 递归查找根节点，同时做路径压缩
            if p[x] != x:  # 当前节点不是根节点
                p[x] = find(p[x])  # 把父指针直接指向根，压缩查找路径
            return p[x]  # 返回根节点

        p = list(range(len(edges)))  # 父数组：节点 1..n 对应下标 0..n-1，初始时各自成一个集合
        for a, b in edges:  # 按顺序逐条加边
            pa, pb = find(a - 1), find(b - 1)  # 分别找出两端点所在集合的根
            if pa == pb:  # 两个端点已经连通，再加这条边就会成环
                return [a, b]  # 这条边就是多余的边
            p[pa] = pb  # 合并两个集合：把一棵树的根挂到另一棵上
