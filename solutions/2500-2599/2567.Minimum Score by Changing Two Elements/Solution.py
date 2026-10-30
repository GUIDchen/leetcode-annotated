# 题目：2567. 修改两个元素的最小分数（Minimum Score by Changing Two Elements）
# 思路：先排序；改两个元素等价于「丢掉两个元素」，剩下 n-2 个元素的分数由最大值减最小值决定，枚举丢弃的三种位置组合取最小跨度。
# 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(n)，Python 的 sort 会申请临时空间。
class Solution:  # LeetCode 约定的题解类
    def minimizeSum(self, nums: List[int]) -> int:  # nums：允许修改两个元素的数组
        nums.sort()  # 原地升序排序，使最小分数只取决于若干首尾元素
        return min(nums[-1] - nums[2], nums[-2] - nums[1], nums[-3] - nums[0])  # 三种丢弃方式：丢最小两个、各丢首尾一个、丢最大两个，取跨度最小者
