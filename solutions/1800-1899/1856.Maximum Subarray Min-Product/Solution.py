# 题目：1856. 子数组最小乘积的最大值（Maximum Subarray Min-Product）
# 思路：单调栈分别求每个元素左边第一个更小值与右边第一个更小值的下标，框出以它为最小值的最大区间；前缀和 O(1) 求区间和，最后取所有 min-product 的最大值再取模。
# 时间复杂度：O(n)，每个下标最多入栈出栈各一次；空间复杂度：O(n)，left/right 数组与前缀和。
class Solution:  # LeetCode 约定的题解类
    def maxSumMinProduct(self, nums: List[int]) -> int:  # nums：正整数数组，求「最小值 × 子数组和」的最大值
        n = len(nums)  # n：数组长度
        left = [-1] * n  # left[i]：i 左边第一个严格更小值下标，默认 -1
        right = [n] * n  # right[i]：i 右边第一个小于等于 nums[i] 的下标，默认 n
        stk = []  # 单调栈：存下标，对应值自底向上递增
        for i, x in enumerate(nums):  # 第一趟：从左往右求左边界
            while stk and nums[stk[-1]] >= x:  # 栈顶值不小于 x，它不可能成为当前元素左边第一个更小值
                stk.pop()  # 弹出，保持栈单调
            if stk:  # 栈非空则栈顶就是左边第一个更小值
                left[i] = stk[-1]  # 记录左边界
            stk.append(i)  # 当前下标入栈
        stk = []  # 清空栈，供第二趟复用
        for i in range(n - 1, -1, -1):  # 第二趟：从右往左求右边界
            while stk and nums[stk[-1]] > nums[i]:  # 严格大于：相等的值只在左侧统计一次，避免重复计算同一区间
                stk.pop()  # 弹出
            if stk:  # 栈非空则栈顶是右边第一个更小值
                right[i] = stk[-1]  # 记录右边界
            stk.append(i)  # 入栈
        s = list(accumulate(nums, initial=0))  # 前缀和，initial=0 让 s[0] = 0
        mod = 10**9 + 7  # 取模常数
        return max((s[right[i]] - s[left[i] + 1]) * x for i, x in enumerate(nums)) % mod  # 每个位置作为区间最小值，区间和为 s[right[i]] - s[left[i] + 1]，取最大值后取模
