# 题目：2832. 每个元素为最大值的最大范围（Maximal Range That Each Element Is Maximum in It）
# 思路：单调栈。分别用一次从前往后、一次从后往前的扫描，求出每个位置左边/右边最近的「严格大于」它的下标；夹在两个边界之间的区间内所有值都不超过 nums[i]，长度即 r-l-1，相等元素因允许同区间而在弹栈时被 <= 一并弹出。
# 时间复杂度：O(n)，每个下标最多入栈出栈各一次；空间复杂度：O(n)，left、right 两个数组与单调栈。
class Solution:  # LeetCode 约定的题解类
    def maximumLengthOfRanges(self, nums: List[int]) -> List[int]:  # nums：输入数组，返回每位置对应的最大区间长度
        n = len(nums)  # 数组长度
        left = [-1] * n  # left[i]：i 左边最近的数值严格大于 nums[i] 的下标，不存在则为 -1
        right = [n] * n  # right[i]：i 右边最近的数值严格大于 nums[i] 的下标，不存在则为 n
        stk = []  # 单调栈（存下标），栈内下标对应的值从底到顶单调递减
        for i, x in enumerate(nums):  # 从左往右扫描，处理左边界
            while stk and nums[stk[-1]] <= x:  # 栈顶值不比 x 大，就不可能成为 x 的严格上界
                stk.pop()  # 弹出，同时保持栈内单调
            if stk:  # 弹完后栈顶就是左边最近的严格更大元素
                left[i] = stk[-1]  # 记录左边界
            stk.append(i)  # 当前下标入栈
        stk = []  # 清空栈，准备反方向再扫一次
        for i in range(n - 1, -1, -1):  # 从右往左扫描，处理右边界
            while stk and nums[stk[-1]] <= nums[i]:  # 弹出所有不大于 nums[i] 的栈顶下标
                stk.pop()  # 它们不构成严格更大的右边界
            if stk:  # 剩下的栈顶就是右边最近的严格更大元素
                right[i] = stk[-1]  # 记录右边界
            stk.append(i)  # 当前下标入栈，维持单调性
        return [r - l - 1 for l, r in zip(left, right)]  # 开区间 (l, r) 的长度即每个位置的最大区间长度
