# 题目：2733. 既不是最小值也不是最大值（Neither Minimum nor Maximum）
# 思路：先用 min/max 求出数组的最小值与最大值，再用生成器表达式找第一个两者都不是的元素，找不到时返回 -1。
# 时间复杂度：O(n)，最多完整扫描两遍；空间复杂度：O(1)，只用了几个标量变量。
class Solution:  # LeetCode 约定的题解类
    def findNonMinOrMax(self, nums: List[int]) -> int:  # nums 是输入数组，返回任意一个既非最小也非最大的元素
        mi, mx = min(nums), max(nums)  # 同时求出数组的最小值与最大值，作为后续筛选的两个基准
        return next((x for x in nums if x != mi and x != mx), -1)  # next 只取生成器的第一个匹配项；若没有匹配项则返回默认值 -1
