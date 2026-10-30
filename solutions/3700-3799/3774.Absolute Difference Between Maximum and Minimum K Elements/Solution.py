# 3774. 最大和最小 K 个元素的绝对差 / Absolute Difference Between Maximum and Minimum K Elements
# 核心思路：排序后最大的 k 个元素在末尾、最小的 k 个元素在开头，两组求和后相减即为绝对差。
# 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)，其中 n 为数组长度（切片产生新列表）。
class Solution:  # 定义题解类
    def absDifference(self, nums: List[int], k: int) -> int:  # 返回最大 k 个元素之和与最小 k 个元素之和的绝对差
        nums.sort()  # 升序排序，让最值都落在两端
        return sum(nums[-k:]) - sum(nums[:k])  # 末尾 k 个之和减去开头 k 个之和
