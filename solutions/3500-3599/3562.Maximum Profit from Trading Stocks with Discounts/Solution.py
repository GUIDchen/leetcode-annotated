# 3562. 折扣价交易股票的最大利润 / Maximum Profit from Trading Stocks with Discounts
# 核心思路：树上背包 DP。dfs(u) 返回表 f[预算][父结点是否购买]，先把各子树的背包合并到 nxt，再决定当前结点买或不买；父结点已购买时 u 可享受半价。
# 复杂度：时间 O(n * budget^2)，空间 O(n * budget)
class Solution:  # 定义解题类
    def maxProfit(  # 返回总预算内能获得的最大利润
        self,  # self 参数
        n: int,  # 商品件数
        present: List[int],  # 每件商品的原价
        future: List[int],  # 每件商品的卖出价
        hierarchy: List[List[int]],  # 上下级关系
        budget: int,  # 总预算
    ) -> int:  # 返回最大利润
        max = lambda a, b: a if a > b else b  # 定义局部求最大值的函数，避免调用内建 max
        g = [[] for _ in range(n + 1)]  # 邻接表，记录每个上司的直接下属
        for u, v in hierarchy:  # 遍历上下级关系建立树形结构
            g[u].append(v)  # 把下属挂到上司下面

        def dfs(u: int):  # 递归计算结点 u 的背包表，第二维 0/1 表示父结点是否购买
            nxt = [[0, 0] for _ in range(budget + 1)]  # 合并完所有子树后的背包表
            for v in g[u]:  # 逐个枚举子结点做分组背包合并
                fv = dfs(v)  # 先算出子结点 v 的背包表
                for j in range(budget, -1, -1):  # 倒序枚举当前容量，避免重复选取
                    for jv in range(j + 1):  # 枚举分给子结点 v 的预算 jv
                        for pre in (0, 1):  # 分别处理父结点未买/已买两种情况
                            val = nxt[j - jv][pre] + fv[jv][pre]  # 前面部分与子树的利润相加
                            if val > nxt[j][pre]:  # 若更优则更新
                                nxt[j][pre] = val  # 记录更大的利润

            f = [[0, 0] for _ in range(budget + 1)]  # 当前结点 u 的背包表
            price = future[u - 1]  # u 的卖出价（下标转 0 基）

            for j in range(budget + 1):  # 枚举可用预算
                for pre in (0, 1):  # 枚举父结点是否购买
                    cost = present[u - 1] // (pre + 1)  # 父结点已买则享受半价
                    if j >= cost:  # 预算足够买下 u
                        f[j][pre] = max(nxt[j][0], nxt[j - cost][1] + (price - cost))  # 不买 u 与买 u 两种选择取较优
                    else:  # 预算不足时
                        f[j][pre] = nxt[j][0]  # 只能放弃 u

            return f  # 返回 u 的背包表

        return dfs(1)[budget][0]  # 根结点没有父结点可买，取预算 budget 下的最优值
