# 题目：2057. 值相等的最小索引（Smallest Index With Equal Value）
# 思路：从左到右枚举下标 i，返回第一个满足 i % 10 == nums[i] 的下标；全都不满足则返回 -1。
# 时间复杂度：O(n)，最坏需要扫完整个数组；空间复杂度：O(1)，只需要常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestEqual(self, nums: List[int]) -> int:  # nums：输入数组；返回满足条件的最小下标
        for i, x in enumerate(nums):  # 同时拿到下标 i 和元素值 x，枚举顺序天然从小到大
            if i % 10 == x:  # 题目条件：下标对 10 取模的结果等于该位置的值
                return i  # 第一个命中的下标就是最小下标，立即返回
        return -1  # 遍历结束仍未命中，按题意返回 -1
