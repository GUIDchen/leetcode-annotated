# 题目：962. 最大宽度坡（Maximum Width Ramp）
# 思路：用单调递减栈保存候选左端点，再从右往左扫描，把每个右端点与栈顶比较并弹出已匹配完的左端点，过程中更新最大宽度。
# 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def maxWidthRamp(self, nums: List[int]) -> int:  # nums 是输入数组，返回满足 i<j 且 nums[i]<=nums[j] 的最大宽度 j-i
        stk = []  # 单调递减栈，存放候选左端点的下标
        for i, v in enumerate(nums):  # 同时取得下标 i 与元素值 v
            if not stk or nums[stk[-1]] > v:  # 比栈顶更小的值才入栈，值更大的左端点不可能给出更宽的坡
                stk.append(i)  # 把当前下标作为候选左端点压栈
        ans = 0  # ans：最大宽度，初始为 0
        for i in range(len(nums) - 1, -1, -1):  # 从右往左扫描，当前下标作为右端点
            while stk and nums[stk[-1]] <= nums[i]:  # 栈顶值不大于 nums[i]，说明这是一段合法坡
                ans = max(ans, i - stk.pop())  # 先算出宽度更新答案，再弹出栈顶（已被最靠右的右端点匹配完）
            if not stk:  # 栈空说明所有候选左端点都处理完，可以提前结束
                break  # 退出循环，不再继续扫描
        return ans  # 返回最大宽度
