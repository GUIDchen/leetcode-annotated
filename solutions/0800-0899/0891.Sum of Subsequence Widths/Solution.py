# 题目：891. 子序列宽度之和（Sum of Subsequence Widths）
# 思路：排序后按下标结算——第 i 小的数有 2^i 次机会当最小值、2^(n-1-i) 次当最大值，于是答案 = Σ (nums[i] - nums[n-1-i]) * 2^i，全程取模。
# 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(1)，只用若干标量（sort 为原地排序）。
class Solution:  # LeetCode 约定的题解类
    def sumSubseqWidths(self, nums: List[int]) -> int:  # nums：输入数组；返回所有非空子序列宽度之和（对 1e9+7 取模）
        mod = 10**9 + 7  # 取模常量
        nums.sort()  # 原地升序排序：宽度与顺序无关，排序后才能按下标定位最值
        ans, p = 0, 1  # ans 累加答案；p 是 2^i，表示当前下标被选中的方案数
        for i, v in enumerate(nums):  # 同时取出下标 i 和元素值 v
            ans = (ans + (v - nums[-i - 1]) * p) % mod  # v 是第 i 小（正贡献），nums[-i-1] 是第 i 大（负贡献）；Python 的 % 会返回非负结果
            p = (p << 1) % mod  # 幂次翻倍并取模，避免数字无限增长
        return ans  # 返回取模后的答案
