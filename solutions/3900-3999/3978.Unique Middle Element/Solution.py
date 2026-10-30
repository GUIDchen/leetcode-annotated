# 3978. Unique Middle Element | 唯一中间元素（简单）
# 核心思路：取出下标 n // 2 处的中间元素，用 count 统计它出现的次数，次数等于 1 说明中间元素在数组中是唯一的。
# 复杂度：时间 O(n)，一次 count 遍历；空间 O(1)，只用常数个变量。
class Solution:  # 定义题解类
    def isMiddleElementUnique(self, nums: list[int]) -> bool:  # 返回中间元素是否在整个数组中只出现一次
        return nums.count(nums[len(nums) // 2]) == 1  # 统计中间元素（下标 n // 2，偶数长度时取靠右的那个）的出现次数，等于 1 即唯一
