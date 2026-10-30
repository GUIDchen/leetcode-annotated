# 题目：1063. 有效子数组的数目（Number of Valid Subarrays）
# 思路：单调栈从右往左求每个下标右侧第一个更小元素的位置 right[i]，以 i 开头的有效子数组恰有 right[i] - i 个。
# 时间复杂度：O(n)，每个下标最多入栈出栈各一次；空间复杂度：O(n)，right 数组与栈。
class Solution:  # LeetCode 约定的题解类
    def validSubarrays(self, nums: List[int]) -> int:  # nums：输入数组；返回满足「最左元素最小」的子数组个数
        n = len(nums)  # 数组长度
        right = [n] * n  # right[i]：i 右侧第一个严格更小元素的下标；没有更小元素时保留哨兵 n
        stk = []  # 单调栈，存下标，对应数值从栈底到栈顶单调不减
        for i in range(n - 1, -1, -1):  # 从右往左枚举下标
            while stk and nums[stk[-1]] >= nums[i]:  # 栈顶数值不严格更小就不可能成为 i 的右侧第一个更小元素，弹掉
                stk.pop()  # 弹出被淘汰的下标
            if stk:  # 栈非空说明找到了右侧第一个更小元素
                right[i] = stk[-1]  # 记下该位置，它决定以 i 开头的子数组右端点上限
            stk.append(i)  # 当前下标入栈，供更左侧元素作为候选
        return sum(j - i for i, j in enumerate(right))  # 起点 i 的贡献是 right[i] - i，逐个累加得到总数
