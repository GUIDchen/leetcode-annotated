# 题目：3075. 幸福值最大化的选择方案（Maximize Happiness of Selected Children）
# 思路：贪心。降序排序后第 i 轮选当前幸福值最大的孩子，此时它已被前面 i 轮各减 1，实际贡献为 happiness[i] - i，负数按 0 计。
# 时间复杂度：O(n log n)，排序是瓶颈；空间复杂度：O(1)，排序在原数组上进行。
class Solution:  # LeetCode 约定的题解类
    def maximumHappinessSum(self, happiness: List[int], k: int) -> int:  # happiness：每个孩子的幸福值；k：需要选出的孩子数量；返回选中孩子的幸福值之和的最大值
        happiness.sort(reverse=True)  # 幸福值从大到小排序，让越大的值越早被选到、被减的次数越少
        ans = 0  # 累加答案
        for i, x in enumerate(happiness[:k]):  # 只遍历前 k 个（即会被选中的孩子），i 是选择轮次，x 是原始幸福值
            x -= i  # 第 i 轮选中时已被前面 i 轮各削减 1，实际幸福值变成 x - i
            ans += max(x, 0)  # 幸福值不能为负，按 0 计入总和
        return ans  # 返回 k 个孩子幸福值之和的最大值
