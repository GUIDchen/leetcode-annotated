# 3535. 单位转换 II / Unit Conversion II
# 核心思路：以单位 0 为根，DFS 求出 0 到每个单位的累计倍率 res；任意 x→y 的倍率即 res[y] / res[x]，用 pow 求模逆元。
# 复杂度：时间 O(n + q log MOD)，空间 O(n)。
class Solution:  # 定义题解类
    def queryConversions(  # 方法签名（分行书写）
        self, conversions: List[List[int]], queries: List[List[int]]  # 参数：conversions 转换关系，queries 查询列表
    ) -> List[int]:  # 返回每个查询的换算倍率（取模）
        def dfs(s: int, mul: int) -> None:  # 深度优先遍历，mul 为 0→s 的累计倍率
            res[s] = mul  # 记录 0→s 的累计倍率
            for t, w in g[s]:  # 遍历 s 的出边
                dfs(t, mul * w % mod)  # 递归孩子，倍率相乘并取模

        mod = 10**9 + 7  # 取模常数
        n = len(conversions) + 1  # 节点数 = 边数 + 1
        g = [[] for _ in range(n)]  # 邻接表
        for s, t, w in conversions:  # 根据转换关系建图
            g[s].append((t, w))  # 记录边 (目标单位, 倍率)
        res = [0] * n  # res[i]：0→i 的累计倍率
        dfs(0, 1)  # 从 0 出发，初始倍率 1
        ans = []  # 存放每个查询的答案
        for x, y in queries:  # 逐个处理查询
            ans.append(res[y] * pow(res[x], mod - 2, mod) % mod)  # res[y] 乘 res[x] 的模逆元
        return ans  # 返回全部答案
