# 3979. Maximum Valid Pair Sum | 最大有效数对和（中等）
# 核心思路：约束是两个下标至少相隔 k。把右端点 j 从小到大扫一遍，同时用变量 x 维护 j - k 及其左侧出现过的最大值，这样 x + nums[j] 就是固定右端点时的最大合法数对和，取全局最大值即可。
# 复杂度：时间 O(n)，一次遍历；空间 O(1)，只用常数个变量。
class Solution:  # 定义题解类
    def maxValidPairSum(self, nums: list[int], k: int) -> int:  # 返回所有下标间隔不小于 k 的数对的最大和
        ans = x = 0  # ans 记录最大数对和；x 维护 nums[j - k] 及其左侧元素的最大值
        for j in range(k, len(nums)):  # 让 j 从 k 开始，保证左侧至少有下标 j - k 可用
            y = nums[j]  # 数对的右元素
            x = max(x, nums[j - k])  # 把下标 j - k 纳入候选，x 始终是左侧（下标 <= j - k）的最大值
            ans = max(ans, x + y)  # 用“左侧最大值 + 当前元素”更新答案
        return ans  # 返回最大有效数对和
