# 题目：3244. 新增道路查询后的最短距离 II（Shortest Distance After Road Addition Queries II）
# 思路：用 nxt 维护链 0->1->...->(n-1)，新边覆盖的中间点直接从链上删除，链上剩余边数 cnt 就是答案。
# 时间复杂度：O(n+q)，每个点最多被删除一次；空间复杂度：O(n)，nxt 数组与答案数组。
class Solution:  # # LeetCode 约定的题解类
    def shortestDistanceAfterQueries(  # # 主方法：n 为城市数，queries 为依次新增的道路
        self, n: int, queries: List[List[int]]  # # self 是实例本身，n 为节点数，queries 为新增道路列表
    ) -> List[int]:  # # 返回每次加边后 0 到 n-1 的最短距离列表
        nxt = list(range(1, n))  # # nxt[i] 是 i 在链上的下一个点，初始即 i+1（最后一个点不在数组里）
        ans = []  # # ans 收集每次加边后的答案
        cnt = n - 1  # # cnt 维护当前链上的边数，也就是最短距离
        for u, v in queries:  # # 依次处理每条新增道路
            if 0 < nxt[u] < v:  # # 只有 u 还没被删除（nxt[u] > 0）且新边确实能缩短链时才处理
                i = nxt[u]  # # 从 u 原来的下一个点开始，逐个跳过被新边覆盖的点
                while i < v:  # # 被覆盖的区间是 [nxt[u], v)
                    cnt -= 1  # # 每跳过一个点，链上就少一条边
                    nxt[i], i = 0, nxt[i]  # # 元组赋值先算右边：i 取旧后继，同时把 nxt[i] 置 0 表示该点已删除
                nxt[u] = v  # # 让 u 直接指向 v，完成链的压缩
            ans.append(cnt)  # # 当前链上剩余的边数就是最短距离
        return ans  # # 返回全部答案
