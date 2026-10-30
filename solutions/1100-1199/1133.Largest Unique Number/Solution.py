# 题目：1133. 最大唯一数（Largest Unique Number）
# 思路：先用计数数组统计每个数出现的次数，再从最大值 1000 向下扫描，第一个出现次数恰好为 1 的数就是答案；若没有唯一数则返回 -1。
# 时间复杂度：O(n + V)，V 为数值上界 1000，可视为常数；空间复杂度 O(V)，计数数组大小固定。
class Solution:  # LeetCode 约定的题解类
    def largestUniqueNumber(self, nums: List[int]) -> int:  # nums：整数数组；返回只出现一次的最大值，没有则返回 -1
        cnt = Counter(nums)  # cnt：值 → 出现次数
        return max((x for x, v in cnt.items() if v == 1), default=-1)  # 取所有出现次数为 1 的数中的最大值，没有则返回 -1
