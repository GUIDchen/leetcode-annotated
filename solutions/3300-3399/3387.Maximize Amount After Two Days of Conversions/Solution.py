# 题目：3387. 两天自由外汇交易后的最大货币数（Maximize Amount After Two Days of Conversions）
# 思路：分别对两天的汇率建无向图，DFS 求出「初始货币 → 每种货币」的换算倍数 d1、d2，答案是 max(d1[c] / d2[c])。
# 时间复杂度：O(V + E)，每个货币只访问一次；空间复杂度：O(V + E)，两张图与两张换算表。
class Solution:  # LeetCode 约定的题解类
    def maxAmount(  # 方法签名开始（参数较多，分多行书写）
        self,  # self
        initialCurrency: str,  # initialCurrency：初始货币
        pairs1: List[List[str]],  # pairs1：第一天的汇率对
        rates1: List[float],  # rates1：第一天的汇率
        pairs2: List[List[str]],  # pairs2：第二天的汇率对
        rates2: List[float],  # rates2：第二天的汇率
    ) -> float:  # 返回两天后能得到的最大货币数
        d1 = self.build(pairs1, rates1, initialCurrency)  # 第一天从初始货币出发能换到的倍数表
        d2 = self.build(pairs2, rates2, initialCurrency)  # 第二天从初始货币出发能换到的倍数表
        return max(d1.get(a, 0) / r2 for a, r2 in d2.items())  # 遍历第二天可达的货币：先按第一天倍数 d1 换出，再按第二天汇率 r2 换回，取最大

    def build(  # 辅助方法：建图并求出 init 到各货币的换算倍数
        self, pairs: List[List[str]], rates: List[float], init: str  # pairs：汇率对；rates：汇率；init：起始货币
    ) -> Dict[str, float]:  # 返回「货币 -> 倍数」的字典
        def dfs(a: str, v: float):  # DFS：v 是 init 换成货币 a 的倍数
            d[a] = v  # 记录当前货币的倍数（同时作为已访问标记）
            for b, r in g[a]:  # 枚举 a 的所有邻居
                if b not in d:  # 邻居还没被算过
                    dfs(b, v * r)  # 递归，倍数累乘

        g = defaultdict(list)  # 邻接表：每个货币 -> [(能换成的货币, 汇率)]
        for (a, b), r in zip(pairs, rates):  # 枚举每个汇率对
            g[a].append((b, r))  # 正向边 a -> b，汇率 r
            g[b].append((a, 1 / r))  # 反向边 b -> a，汇率为倒数
        d = {}  # 换算结果字典，同时充当访问标记
        dfs(init, 1)  # 从初始货币出发，初始倍数为 1
        return d  # 返回整张换算表
