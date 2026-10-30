# 3736. 最小操作次数使数组元素相等 III / Minimum Moves to Equal Array Elements III
# 核心思路：每次操作只能把某个元素加一，因此把所有元素补到数组最大值即可，答案是最大值乘以元素个数减去元素总和。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义 LeetCode 解法类
    def minMoves(self, nums: List[int]) -> int:  # 返回使所有元素相等所需的最小操作次数
        n = len(nums)  # 数组长度
        mx = max(nums)  # 数组中的最大值
        s = sum(nums)  # 数组元素之和
        return mx * n - s  # 每个元素补到最大值的差值之和即为操作次数
