# 题目：3221. 最大数组跳跃得分 II（Maximum Array Hopping Score II）
# 思路：单调栈去掉所有「右侧存在更大值」的下标，留下一条后缀最大值链；从 0 依次跳过去，每段贡献 (j-i)*nums[j]。
# 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，单调栈最多保存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, nums: List[int]) -> int:  # nums 是跳跃得分的输入数组
        stk = []  # 单调（不增）栈：保存候选落点的下标，栈内数值从下到上单调不增
        for i, x in enumerate(nums):  # 同时取出下标 i 与元素值 x
            while stk and nums[stk[-1]] <= x:  # 栈顶的值小于等于 x，说明它被 x 支配，不可能是最优落点
                stk.pop()  # 弹出被支配的下标
            stk.append(i)  # 当前下标入栈，维持栈内数值单调不增
        ans = i = 0  # ans 累计得分；i 是上一次的落点下标，起点为 0
        for j in stk:  # 按栈内顺序依次经过每个保留下来的落点
            ans += nums[j] * (j - i)  # 从 i 跳到 j 共 j-i 步，每步获得 nums[j] 的得分
            i = j  # 更新落点，供下一段使用
        return ans  # 返回最大跳跃得分
