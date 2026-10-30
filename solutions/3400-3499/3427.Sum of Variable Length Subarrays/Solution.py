# 3427. Sum of Variable Length Subarrays / 3427. 变长子数组求和
# 核心思路：前缀和预处理，以 i 结尾的子数组和等于 s[i + 1] - s[max(0, i - x)]。
# 复杂度：时间 O(n)，空间 O(n)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def subarraySum(self, nums: List[int]) -> int:  # 返回所有变长子数组的元素和之和
        s = list(accumulate(nums, initial=0))  # 前缀和数组：initial=0 使 s[i + 1] - s[j] 恰为 nums[j..i] 之和
        return sum(s[i + 1] - s[max(0, i - x)] for i, x in enumerate(nums))  # 枚举右端点 i 与对应值 x，左端点下界为 max(0, i - x)，逐段累加区间和
