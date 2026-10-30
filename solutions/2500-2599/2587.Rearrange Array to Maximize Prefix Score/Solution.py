# 题目：2587. 重排数组以得到最大前缀分数（Rearrange Array to Maximize Prefix Score）
# 思路：要让前缀和尽量大，就把大正数放前面，因此降序排序后逐个累加；一旦前缀和 <= 0，后面只会更小，直接返回已统计的个数。
# 时间复杂度：O(n log n)，排序开销；空间复杂度：O(1) 额外空间（nums.sort 为原地排序）。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, nums: List[int]) -> int:  # nums 为可任意重排的数组；返回正前缀和的最大个数
        nums.sort(reverse=True)  # 原地降序排序，让大的正数排在前面以最大化前缀和
        s = 0  # 当前前缀和（Python 整数不会溢出，无需 long）
        for i, x in enumerate(nums):  # 从头开始累加前缀和
            s += x  # 把当前元素并入前缀和
            if s <= 0:  # 前缀和非正，之后的元素更小，前缀和不可能再变正
                return i  # 前面 i 个前缀都是正的，所以得分是 i
        return len(nums)  # 所有前缀都为正，得分为数组长度
