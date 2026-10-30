# 3652. 按策略买卖股票的最佳时机（Best Time to Buy and Sell Stock using Strategy）
# 核心思路：用前缀和 s 记录「策略*股价」的贡献、t 记录股价和；枚举长度为 k 的修改窗口，窗口前 k/2 天改为持有（贡献归零）、后 k/2 天改为卖出（贡献等于股价），取最大利润。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义题解类
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:  # 返回最多做一次策略修改后的最大利润；k 为偶数，修改窗口长度为 k
        n = len(prices)  # 天数
        s = [0] * (n + 1)  # s 记录 strategy[i]*prices[i] 的前缀和
        t = [0] * (n + 1)  # t 记录 prices 的前缀和
        for i, (a, b) in enumerate(zip(prices, strategy), 1):  # 从前缀和下标 1 开始同时遍历价格与策略
            s[i] = s[i - 1] + a * b  # s 累加原始的「策略 * 股价」贡献
            t[i] = t[i - 1] + a  # t 累加当天股价，供把策略改成 1（卖出）时使用
        ans = s[n]  # 不做任何修改时的利润，作为答案初值
        for i in range(k, n + 1):  # 枚举修改窗口的右端点 i，窗口为 [i-k+1, i]
            ans = max(ans, s[n] - (s[i] - s[i - k]) + t[i] - t[i - k // 2])  # 新利润 = 原总利润 - 窗口内的原贡献 + 窗口后 k/2 天全部卖出的贡献
        return ans  # 返回最大利润
