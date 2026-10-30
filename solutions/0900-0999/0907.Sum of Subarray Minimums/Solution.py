# 题目：907. 子数组的最小值之和（Sum of Subarray Minimums）
# 核心思路：单调栈求出每个元素作为最小值时向左、向右能延伸的边界，再用 (i-left[i])*(right[i]-i) 统计它贡献的子数组个数。
# 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，left/right 数组与栈。
class Solution:  # LeetCode 约定的题解类
    def sumSubarrayMins(self, arr: List[int]) -> int:  # arr：输入数组；返回所有子数组最小值之和（对 1e9+7 取模）
        n = len(arr)  # 数组长度
        left = [-1] * n  # left[i]：i 左边第一个严格小于 arr[i] 的下标，没有则为 -1
        right = [n] * n  # right[i]：i 右边第一个小于等于 arr[i] 的下标，没有则为 n
        stk = []  # 单调递增栈，存下标，栈内对应的值从底到顶递增
        for i, v in enumerate(arr):  # 从左到右扫描，求每个位置的左边界
            while stk and arr[stk[-1]] >= v:  # 栈顶值不小于当前值，不再是左边界的候选
                stk.pop()  # 弹出，保证栈内值严格递增
            if stk:  # 栈顶就是左边第一个比当前值小的元素
                left[i] = stk[-1]  # 记录左边界下标
            stk.append(i)  # 当前下标入栈，作为后续元素的候选

        stk = []  # 清空栈，复用给从右向左的扫描
        for i in range(n - 1, -1, -1):  # 从右到左扫描，求每个位置的右边界
            while stk and arr[stk[-1]] > arr[i]:  # 栈顶值大于当前值，不再可能成为右边界
                stk.pop()  # 弹出，保持栈内值递增
            if stk:  # 栈顶就是右边第一个小于等于当前值的元素
                right[i] = stk[-1]  # 记录右边界下标
            stk.append(i)  # 当前下标入栈
        mod = 10**9 + 7  # 题目要求的取模常量
        return sum((i - left[i]) * (right[i] - i) * v for i, v in enumerate(arr)) % mod  # 每个元素贡献 (i-left[i])*(right[i]-i) 个子数组，求和后取模
