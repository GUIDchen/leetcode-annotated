# 题目：2920. 收集所有金币可获得的最大积分（Maximum Points After Collecting Coins From All Nodes）
# 思路：树上记忆化 DFS，状态为（节点，已整体除以 2 的次数），每个节点枚举「按第二类收集扣 k」与「先除 2 再按第一类收集」两种方案取最大。
# 时间复杂度：O(n·log C)，状态数为 n×15，每个状态遍历一次邻接边；空间复杂度：O(n·log C)，缓存与邻接表。
class Solution:  # LeetCode 约定的题解类
    def maximumPoints(self, edges: List[List[int]], coins: List[int], k: int) -> int:  # edges：树的边；coins：每个节点的金币；k：第二类收集的扣费
        @cache  # 给 dfs 加记忆化，避免同一状态重复计算
        def dfs(i: int, fa: int, j: int) -> int:  # i 当前节点，fa 父节点（防回头），j 已经除以 2 的次数
            a = (coins[i] >> j) - k  # 方案一：在 i 处以第二类方式收集，扣掉 k
            b = coins[i] >> (j + 1)  # 方案二：先把 coins[i] 除以 2，再按第一类收集
            for c in g[i]:  # 枚举 i 的所有邻居
                if c != fa:  # 跳过父节点，避免在树上走回头路
                    a += dfs(c, i, j)  # 方案一：子树继续处于「除了 j 次」的状态
                    if j < 14:  # 再除一次仍在有效范围内（coins 最多 10^4，14 次后必为 0）
                        b += dfs(c, i, j + 1)  # 方案二：子树进入「除了 j+1 次」的状态
            return max(a, b)  # 两种方案取较大者

        n = len(coins)  # 节点个数
        g = [[] for _ in range(n)]  # 邻接表，g[u] 存 u 的所有邻居
        for a, b in edges:  # 逐条边建无向图
            g[a].append(b)  # a 的邻居中加入 b
            g[b].append(a)  # b 的邻居中加入 a
        ans = dfs(0, -1, 0)  # 从根节点 0 出发，还没有做过除法
        dfs.cache_clear()  # 清空闭包缓存，避免污染同一实例上的后续调用
        return ans  # 返回最大积分
