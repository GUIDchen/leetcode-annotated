# 3613. Minimize Maximum Component Cost / 最小化连通分量的最大成本
# 核心思路：把边按权值升序做 Kruskal 合并，连通块数首次降到 k 时最后加入的边权即最小可能的最大分量成本。
# 复杂度：时间复杂度 O(E log E)，空间复杂度 O(n)，E 为边数。
class Solution:  # 定义题解类
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:  # 求把图分成至多 k 个连通块时，各块内最贵边权的最小上界
        def find(x: int) -> int:  # 并查集递归 find：带路径压缩
            if p[x] != x:  # 未指向自己说明还没到根
                p[x] = find(p[x])  # 递归压缩，并把父指针直接更新到根
            return p[x]  # 返回根节点

        if k == n:  # 特判：若每个点自成一 块
            return 0  # 无需任何边，成本为 0
        edges.sort(key=lambda x: x[2])  # 按边权升序排序，为 Kruskal 做准备
        cnt = n  # cnt 记录当前连通块数量，初始 n 块
        p = list(range(n))  # 并查集父数组，初始每个点独立
        for u, v, w in edges:  # 依次尝试加入每条边
            pu, pv = find(u), find(v)  # 找到两个端点所在集合的根
            if pu != pv:  # 只有端点属于不同连通块才合并
                p[pu] = pv  # 合并两个集合
                cnt -= 1  # 连通块数量减一
                if cnt <= k:  # 块数已降到 k 或更少
                    return w  # 当前边权即为最大分量成本的下界
        return 0  # 兜底返回 0
