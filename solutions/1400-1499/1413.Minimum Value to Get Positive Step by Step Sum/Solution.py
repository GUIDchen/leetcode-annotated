# 题目：1413. 逐步求和得到正数的最小值（Minimum Value to Get Positive Step by Step Sum）
# 思路：遍历求最小前缀和 t，起始值取 max(1, 1-t) 即可保证每一步前缀和严格为正。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def minStartValue(self, nums: List[int]) -> int:  # nums 是待累加的数组，返回使每步前缀和为正的最小起始值
        s, t = 0, inf  # s 为当前前缀和，t 用正无穷初始化以记录最小前缀和
        for num in nums:  # 依次遍历每个元素
            s += num  # 累加得到当前前缀和
            t = min(t, s)  # 维护最小前缀和
        return max(1, 1 - t)  # 1-t 让最小值刚好到 1，起始值自身又不能小于 1
