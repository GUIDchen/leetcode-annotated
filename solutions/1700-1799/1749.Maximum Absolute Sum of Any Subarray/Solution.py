# 题目：1749. 任意子数组和的绝对值的最大值（Maximum Absolute Sum of Any Subarray）
# 核心思路：最大绝对值只能由最大子数组和或最小子数组和产生，用 f、g 分别维护以当前元素结尾的最大和与最小和，答案取 max(f, |g|)。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxAbsoluteSum(self, nums: List[int]) -> int:  # nums 是输入数组，返回任意子数组和的绝对值的最大值
        f = g = 0  # f 维护以当前元素结尾的最大和，g 维护以当前元素结尾的最小和
        ans = 0  # 空子数组和为 0，答案从 0 起即可
        for x in nums:  # 逐个元素扩展，枚举以 x 结尾的区间
            f = max(f, 0) + x  # 最大和：负前缀直接丢弃，从 x 重新开始
            g = min(g, 0) + x  # 最小和：正前缀直接丢弃，从 x 重新开始
            ans = max(ans, f, abs(g))  # 最大和与最小和的绝对值都可能成为答案，一起刷新
        return ans  # 返回最大的绝对值
