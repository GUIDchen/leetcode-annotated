# 题目：2289. 使数组按非递减顺序排列（Steps to Make Array Non-decreasing）
# 核心思路：从右往左扫描并用单调栈保存下标，dp[i] 表示削平 nums[i] 右侧严格更小元素所需的轮数，每弹出一个更小的栈顶就更新 max(dp[i]+1, dp[top])，答案取 dp 的最大值。
# 时间复杂度：O(n)，每个下标最多进出栈各一次；空间复杂度：O(n)，栈与 dp 数组。
class Solution:  # LeetCode 约定的题解类
    def totalSteps(self, nums: List[int]) -> int:  # nums：输入列表；返回使整个列表非递减所需的最少轮数
        stk = []  # 单调栈：从右往左保存候选下标，对应数值单调递减
        ans, n = 0, len(nums)  # ans 预留为答案变量（本写法最后统一用 max(dp) 取答案）；n 是数组长度
        dp = [0] * n  # dp[i]：削平 nums[i] 右侧所有更小元素所需的轮数，初始为 0
        for i in range(n - 1, -1, -1):  # 逆序遍历，保证右侧元素的 dp 值先算好
            while stk and nums[i] > nums[stk[-1]]:  # 栈顶元素严格小于 nums[i]，说明它会在某一轮被 nums[i] 删掉
                dp[i] = max(dp[i] + 1, dp[stk.pop()])  # pop 直接取出栈顶的 dp 值：每吸收一个元素自身轮数加 1，但不能早于栈顶被削平
            stk.append(i)  # 当前下标入栈，等待更左侧、更大的元素来结算
        return max(dp)  # 所有元素轮数的最大值即整个数组变非递减的轮数
