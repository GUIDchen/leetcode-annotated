# 题目：84. 柱状图中最大的矩形（Largest Rectangle in Histogram）
# 思路：单调递增栈一次遍历求出每根柱子左右两侧第一个更矮的下标，再以每根柱子为高，用 right - left - 1 作为宽度算面积。
# 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，栈与 left/right 数组。

class Solution:  # LeetCode 约定的题解类
    def largestRectangleArea(self, heights: List[int]) -> int:  # heights：每根柱子的高度
        n = len(heights)  # 柱子总数
        stk = []  # 单调栈，存下标，栈底到栈顶对应的高度严格递增
        left = [-1] * n  # left[i]：i 左边第一个更矮柱子的下标，-1 表示不存在
        right = [n] * n  # right[i]：i 右边第一个更矮柱子的下标，n 表示不存在
        for i, h in enumerate(heights):  # 从左往右扫描，同时确定右边界和左边界
            while stk and heights[stk[-1]] >= h:  # 栈顶不低于当前柱高，说明栈顶的右边界正是 i
                right[stk[-1]] = i  # 记下栈顶柱子的右侧第一个更矮位置
                stk.pop()  # 右边界已确定，把栈顶弹出
            if stk:  # 弹出所有不低于 i 的柱子后栈仍不空
                left[i] = stk[-1]  # 此时栈顶就是 i 左边第一个更矮的柱子
            stk.append(i)  # 当前下标入栈，维持栈内高度递增
        return max(h * (right[i] - left[i] - 1) for i, h in enumerate(heights))  # 以每根柱子为高算面积，取最大值
