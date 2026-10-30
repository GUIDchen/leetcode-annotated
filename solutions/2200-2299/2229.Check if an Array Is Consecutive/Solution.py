# 题目：2229. 检查数组是否连贯（Check if an Array Is Consecutive）
# 思路：求出最小值与最大值，若「去重后个数」「极差 + 1」与「原长度」三者相等，则数组恰好是一段连续整数。
# 时间复杂度：O(n)，求最值与建集合各一次遍历；空间复杂度：O(n)，集合最多保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def isConsecutive(self, nums: List[int]) -> bool:  # nums 为待检查数组；返回它是否构成一段连续整数
        mi, mx = min(nums), max(nums)  # 同时求出最小值与最大值，两者决定候选连续区间的长度
        return len(set(nums)) == mx - mi + 1 == len(nums)  # 链式比较：去重后个数 = 极差 + 1 = 原长度，说明既无重复也无缺失
