# 题目：85. 最大矩形（Maximal Rectangle）
# 思路：逐行把矩阵压成一维柱状图（遇到 "1" 高度加一、遇到 "0" 清零），再对每行用 84 题的方法求最大矩形；这里用左右两次遍历分别求左右边界。
# 时间复杂度：O(m * n)，每行两次 O(n) 的单调栈；空间复杂度：O(n)，高度数组、left/right 数组与栈。

class Solution:  # LeetCode 约定的题解类
    def maximalRectangle(self, matrix: List[List[str]]) -> int:  # matrix：只含 "0"/"1" 的字符矩阵
        heights = [0] * len(matrix[0])  # heights[j]：以当前行为底时第 j 列向上连续 "1" 的高度
        ans = 0  # 记录全矩阵中的最大矩形面积
        for row in matrix:  # 从上到下逐行扫描，把每一行都当作柱状图的底
            for j, v in enumerate(row):  # 逐列更新高度
                if v == "1":  # 当前格是 "1"
                    heights[j] += 1  # 该列连续 "1" 的高度加一
                else:  # 当前格是 "0"
                    heights[j] = 0  # 连续段被打断，高度清零
            ans = max(ans, self.largestRectangleArea(heights))  # 用这一行的柱状图更新答案
        return ans  # 返回最大矩形面积

    def largestRectangleArea(self, heights: List[int]) -> int:  # 单调栈求柱状图最大矩形
        n = len(heights)  # 柱子数量
        stk = []  # 单调栈，存下标，栈底到栈顶对应高度严格递增
        left = [-1] * n  # left[i]：i 左边第一个更矮柱子的下标，-1 表示不存在
        right = [n] * n  # right[i]：i 右边第一个更矮柱子的下标，n 表示不存在
        for i, h in enumerate(heights):  # 第一遍：正序扫描求左边界
            while stk and heights[stk[-1]] >= h:  # 栈顶不低于当前柱高就弹出，保证栈内严格递增
                stk.pop()  # 弹出栈顶，让更矮的柱子露出来
            if stk:  # 栈不空
                left[i] = stk[-1]  # 栈顶就是 i 左边第一个更矮的柱子
            stk.append(i)  # 当前下标入栈
        stk = []  # 清空栈，准备反向扫描
        for i in range(n - 1, -1, -1):  # 第二遍：逆序扫描求右边界
            h = heights[i]  # 当前柱子的高度
            while stk and heights[stk[-1]] >= h:  # 同上，维护严格递增栈
                stk.pop()  # 弹出不低于当前高度的下标
            if stk:  # 栈不空
                right[i] = stk[-1]  # 栈顶就是 i 右边第一个更矮的柱子
            stk.append(i)  # 当前下标入栈
        return max(h * (right[i] - left[i] - 1) for i, h in enumerate(heights))  # 以每根柱子为高算面积，取最大值
