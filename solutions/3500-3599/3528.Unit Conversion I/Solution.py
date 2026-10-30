# 题目：3528. 单位转换 I（Unit Conversion I）
# 思路：把 conversions 看成以 0 号单位为根的有向树，从 0 DFS，把沿途的换算系数连乘（对 1e9+7 取模）即得每个单位折算成 0 号单位的系数。
# 时间复杂度：O(n)，n 为单位个数，每个单位只访问一次；空间复杂度：O(n)，邻接表与答案数组。
class Solution:  # LeetCode 约定的题解类
    def baseUnitConversions(self, conversions: List[List[int]]) -> List[int]:  # conversions[i] = [源单位, 目标单位, 换算系数]
        def dfs(s: int, mul: int) -> None:  # 从 s 深搜，mul 为到 s 为止的累计系数
            ans[s] = mul  # 到达 s 时的累计系数就是它折合 0 号单位的系数
            for t, w in g[s]:  # 枚举 s 的所有后继单位
                dfs(t, mul * w % mod)  # 系数连乘并取模后继续深搜

        mod = 10**9 + 7  # 题目要求的取模值
        n = len(conversions) + 1  # 单位个数 = 换算关系数 + 1
        g = [[] for _ in range(n)]  # 邻接表：g[u] 存 (目标单位, 换算系数)
        for s, t, w in conversions:  # 逐条建立有向边
            g[s].append((t, w))  # 源单位指向目标单位，边权为换算系数
        ans = [0] * n  # ans[u] 表示 1 个 u 单位折合多少个 0 号单位
        dfs(0, 1)  # 从 0 号单位出发，系数为 1
        return ans  # 返回每个单位折算成 0 号单位的系数
