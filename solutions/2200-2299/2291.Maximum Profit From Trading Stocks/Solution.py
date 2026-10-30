# 题目：2291. 最大股票收益（Maximum Profit From Trading Stocks）
# 核心思路：0-1 背包。买入第 i 只股票花费 present[i]、收益为 future[i]-present[i]，用二维 dp 求预算内的最大收益。
# 时间复杂度：O(n * budget)，双层循环遍历股票与预算；空间复杂度：O(n * budget)，二维 dp 表。
class Solution:  # LeetCode 约定的题解类
    def maximumProfit(self, present: List[int], future: List[int], budget: int) -> int:  # present：买入价；future：一年后价格；budget：预算上限
        f = [[0] * (budget + 1) for _ in range(len(present) + 1)]  # f[i][j]：前 i 只股票、预算为 j 时的最大收益；整体初始化为 0
        for i, w in enumerate(present, 1):  # i 从 1 开始编号表示「前 i 只」，w 是第 i 只股票的买入价
            for j in range(budget + 1):  # 枚举所有可能的预算上限
                f[i][j] = f[i - 1][j]  # 不买第 i 只股票，直接继承上一行状态
                if j >= w and future[i - 1] > w:  # 预算够买且该股票确有正收益才值得买，否则买入只会拉低收益
                    f[i][j] = max(f[i][j], f[i - 1][j - w] + future[i - 1] - w)  # 买入的收益 = future-w，再加上剩余预算 j-w 下的最优解，与不买方案取较大值
        return f[-1][-1]  # 最后一行最后一列即全部股票、完整预算下的最优收益
