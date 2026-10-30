# 题目：1319. 连通网络的操作次数（Number of Operations to Make Network Connected）
# 思路：并查集合并已有连接，统计多余边数 cnt；连通 k 个连通块需 k-1 条边，边够则答案为 k-1，否则 -1。
# 时间复杂度：O(m·α(n))，并查集近似常数；空间复杂度：O(n)，父数组。
class Solution:  # LeetCode 约定的题解类
    def makeConnected(self, n: int, connections: List[List[int]]) -> int:  # n 为计算机数，connections 为已有网线连接
        def find(x: int) -> int:  # 带路径压缩的递归查找函数
            if p[x] != x:  # 若当前节点不是根
                p[x] = find(p[x])  # 递归找到根并挂上去，压缩查询路径
            return p[x]  # 返回当前节点所在连通块的根

        cnt = 0  # cnt 统计多余的边（可挪用重连的网线数）
        p = list(range(n))  # 并查集父数组，初始时每个节点自成一类
        for a, b in connections:  # 逐条处理已有连接
            pa, pb = find(a), find(b)  # 分别求两个端点所在连通块的根
            if pa == pb:  # 两端已连通，这条边多余
                cnt += 1  # 多余边数加一
            else:  # 否则两个连通块需要合并
                p[pa] = pb  # 把一棵树的根挂到另一棵的根上
                n -= 1  # 合并后连通块数减一（n 复用为剩余块数）
        return -1 if n - 1 > cnt else n - 1  # 连通 n 个块需 n-1 条边：多余边不够则返回 -1，否则返回 n-1
