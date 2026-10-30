# 题目：1150. 检查一个数是否在数组中占绝大多数（Check If a Number Is Majority Element in a Sorted Array）
# 思路：数组升序，用两次二分分别求出 target 的起始与结束位置，出现次数严格大于 n/2 即为绝大多数。
# 时间复杂度：O(log n)，两次二分查找；空间复杂度：O(1)，只用两个下标变量。
class Solution:  # LeetCode 约定的题解类
    def isMajorityElement(self, nums: List[int], target: int) -> bool:  # nums 升序，target 是要检查的数
        left = bisect_left(nums, target)  # 第一个等于 target 的下标
        right = bisect_right(nums, target)  # 第一个大于 target 的下标
        return right - left > len(nums) // 2  # 出现次数超过一半才算绝大多数
