# 题目：2312. 卖木头块（Selling Pieces of Wood）
# 思路：记忆化搜索。dfs(h, w) 求 h×w 木块能卖出的最大钱数：先取整块直接卖的价格 d[h][w]，再枚举横切与竖切的位置（只枚举到一半，另一半对称），把两块的 dfs 值相加，最后取最大值并由 @cache 缓存。
# 时间复杂度：O(m·n·(m+n))，共 m·n 个状态，每个状态枚举 O(h+w) 种切法；空间复杂度：O(m·n)，缓存与价格表。
class Solution:  # LeetCode 约定的题解类
    def sellingWood(self, m: int, n: int, prices: List[List[int]]) -> int:  # prices 每项是 [高, 宽, 价格]，返回能卖出的最大总价
        @cache  # 装饰器：缓存 dfs 的返回值，同一尺寸只算一次
        def dfs(h: int, w: int) -> int:  # 求 h×w 木块能卖出的最大钱数
            ans = d[h].get(w, 0)  # 方案一：整块直接卖；d[h] 中没有宽度 w 的报价时默认 0
            for i in range(1, h // 2 + 1):  # 枚举横向切分位置，只枚举到一半，另一半对称
                ans = max(ans, dfs(i, w) + dfs(h - i, w))  # 上下两块各自取最优后相加
            for i in range(1, w // 2 + 1):  # 枚举纵向切分位置，同样只枚举到一半
                ans = max(ans, dfs(h, i) + dfs(h, w - i))  # 左右两块各自取最优后相加
            return ans  # 返回该尺寸的最优收益

        d = defaultdict(dict)  # 二维价格表：d[高][宽] = 整块卖出的价格
        for h, w, p in prices:  # 逐条读入报价
            d[h][w] = p  # 记录该尺寸的整块价格
        return dfs(m, n)  # 从整块 m×n 开始求解
