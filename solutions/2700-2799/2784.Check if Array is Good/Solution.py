# 题目：2784. 检查数组是否是好的（Check if Array is Good）
# 核心思路：计数。好数组必是 1..n 各出现一次再加一个 n，故用 Counter 统计后检查 n 出现 2 次、1..n-1 都出现过。
# 时间复杂度：O(n)，统计与检查各扫一遍；空间复杂度：O(n)，哈希计数表。
class Solution:  # LeetCode 约定的题解类
    def isGood(self, nums: List[int]) -> bool:  # nums：待检查数组；返回它是否是好数组
        cnt = Counter(nums)  # Counter 统计每个值出现的次数（没出现的键访问时返回 0）
        n = len(nums) - 1  # 好数组长度是 n+1，所以 n = len(nums) - 1
        return cnt[n] == 2 and all(cnt[i] for i in range(1, n))  # 条件一：最大值 n 恰好出现两次；条件二：1..n-1 每个值都出现过（计数非 0 即真，n = 1 时区间为空也成立）
