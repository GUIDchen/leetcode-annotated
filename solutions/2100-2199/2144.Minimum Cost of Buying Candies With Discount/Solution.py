# 题目：2144. 打折购买糖果的最小开销（Minimum Cost of Buying Candies With Discount）
# 思路：降序排序后每 3 颗一组，每组第 3 贵的那颗免费；用总价减去所有下标 2,5,8… 的价格即为答案。
# 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，排序在原列表上原地完成。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, cost: List[int]) -> int:  # cost：每颗糖果的价格列表
        cost.sort(reverse=True)  # 原地降序排序，保证免费的总是每组里最便宜的一颗
        return sum(cost) - sum(cost[2::3])  # 总价减去下标 2,5,8…（每组第 3 颗、免费）的价格之和
