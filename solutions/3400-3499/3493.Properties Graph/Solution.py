# 3493. Properties Graph / 3493. 属性图
# 核心思路：把每个数组去重成集合，两两求交集，交集大小至少为 k 的两点连边，最后用 DFS 统计连通分量个数。
# 复杂度：时间 O(n^2 * m)，其中 m 为单个属性数组长度上界；空间 O(n^2)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:  # properties 为各点属性数组，k 为连边所需的公共属性数
        def dfs(i: int) -> None:  # 递归 DFS，遍历并标记 i 所在的整个连通分量
            vis[i] = True  # 标记当前点已访问
            for j in g[i]:  # 遍历 i 的所有邻居
                if not vis[j]:  # 邻居未被访问才继续递归
                    dfs(j)  # 深入该邻居

        n = len(properties)  # 点的个数
        ss = list(map(set, properties))  # 每个数组去重成集合，便于求交集大小
        g = [[] for _ in range(n)]  # 邻接表，g[i] 存放与 i 公共属性数达到 k 的点
        for i, s1 in enumerate(ss):  # 枚举点对中较大的下标 i 及其属性集合
            for j in range(i):  # 只枚举 j < i，保证每对点只处理一次
                s2 = ss[j]  # 取 j 的属性集合
                if len(s1 & s2) >= k:  # 公共属性数达到 k，两点之间建双向边
                    g[i].append(j)  # 从 i 连向 j
                    g[j].append(i)  # 从 j 连向 i
        ans = 0  # 连通分量计数
        vis = [False] * n  # vis[i] 标记点 i 是否已被访问
        for i in range(n):  # 枚举每个点作为连通分量的起点
            if not vis[i]:  # 发现未访问的点，说明是一个新分量
                dfs(i)  # 标记整个分量
                ans += 1  # 分量计数加一
        return ans  # 返回连通分量个数
