# 题目：1561. 你可以获得的最大硬币数目（Maximum Number of Coins You Can Get）
# 思路：升序排序后，最小的三分之一给对手；剩余部分每隔一堆取一堆，就是每组的中位数。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，除原地排序外只用常数空间。
class Solution:  # LeetCode 约定的题解类
    def maxCoins(self, piles: List[int]) -> int:  # piles：每堆硬币数
        piles.sort()  # 原地升序排序，方便按大小分组
        return sum(piles[len(piles) // 3 :][::2])  # 跳过最小的三分之一（给对手），再从剩余部分每隔一堆取一堆（每组的中位数）求和
