# 题目：261. 以图判树（Graph Valid Tree）
# 思路：并查集（路径压缩）。树要求连通且无环：逐条边合并端点，出现同根即有环；每合并一次把 n 减一，最后 n == 1 表示恰好形成一棵树。
# 时间复杂度：O(n α(n))，α 为反阿克曼函数；空间复杂度：O(n)，父数组 p。

class Solution:  # LeetCode 约定的题解类
    def validTree(self, n: int, edges: List[List[int]]) -> bool:  # n：节点数；edges：无向边列表
        def find(x: int) -> int:  # 查找 x 所在集合的根，并做路径压缩
            if p[x] != x:  # x 不是根（父节点不是自己）
                p[x] = find(p[x])  # 递归找到根，并让 p[x] 直接指向根
            return p[x]  # 返回根节点

        p = list(range(n))  # 父数组：初始时每个节点自成一个集合
        for a, b in edges:  # 逐条边尝试合并两个端点
            pa, pb = find(a), find(b)  # 分别求两个端点所在集合的根
            if pa == pb:  # 两端点已连通
                return False  # 再加这条边必然成环，不是树
            p[pa] = pb  # 合并集合：把 pa 的根挂到 pb 的根下
            n -= 1  # 成功合并一次，连通分量数减一
        return n == 1  # 只剩一个连通分量才算树
