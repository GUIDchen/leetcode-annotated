# 题目：2551. 将珠子放入背包中（Put Marbles in Bags）
# 思路：得分 = weights[0] + weights[n-1] + (k-1) 个相邻对的和，两端项在最大/最小得分中相互抵消；对相邻对之和排序后，用最大的 k-1 个之和减最小的 k-1 个之和。
# 时间复杂度：O(n log n)，由排序决定；空间复杂度：O(n)，arr 保存 n-1 个相邻对之和。
class Solution:  # LeetCode 约定的题解类
    def putMarbles(self, weights: List[int], k: int) -> int:  # weights 是珠子的重量；k 是要分成的袋子数
        arr = sorted(a + b for a, b in pairwise(weights))  # pairwise(weights) 给出所有相邻对，求和后升序排序，共 n-1 个
        return sum(arr[len(arr) - k + 1 :]) - sum(arr[: k - 1])  # 尾部的 k-1 个较大相邻和 减去 头部 k-1 个较小相邻和（两端的固定项互相抵消）
