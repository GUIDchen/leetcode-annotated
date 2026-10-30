# 题目：2898. 最大线性股票得分（Maximum Linear Stock Score）
# 思路：线性序列要求 prices 的差值等于下标差，即 prices[i] - i 相同的股价属于同一组；把同组股价求和，取最大组和。
# 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，计数器最多存 n 个差值。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, prices: List[int]) -> int:  # prices：每日股价数组
        cnt = Counter()  # cnt[d]：所有满足 prices[i] - i == d 的股价之和
        for i, x in enumerate(prices):  # 同时取得下标 i 与股价 x
            cnt[x - i] += x  # 差值相同的股价属于同一个线性序列，累加得分
        return max(cnt.values())  # 返回所有分组和中的最大值
