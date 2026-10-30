# 题目：4035. 最多有效分割位置 I / Maximum Valid Split Positions I
# 核心思路：暴力枚举被删除的下标（含不删除），对得到的每个数组用前缀 gcd 与后缀 gcd 比对来统计有效分割位置
# 复杂度：时间复杂度 O(n^2 log V)，空间复杂度 O(n)
class Solution:  # 定义 LeetCode 题解类
    def maxValidSplits(self, nums: List[int]) -> int:  # 允许删除至多一个元素，返回能得到的最大有效分割位置个数
        def calc(arr: List[int]) -> int:  # 闭包：统计 arr 中满足前缀 gcd 等于后缀 gcd 的分割位置个数
            m = len(arr)  # 当前数组长度
            pre = list(accumulate(arr, gcd))  # pre[i] 为前 i+1 个元素的前缀 gcd
            suf = list(accumulate(arr[::-1], gcd))[::-1]  # 倒序累加再反转，得到 suf[i] 为从 i 开始的后缀 gcd
            return sum(pre[i] == suf[i + 1] for i in range(m - 1))  # 统计所有分割点中左右两段 gcd 相等的个数

        ans = calc(nums)  # 先考虑不删除任何元素的情况
        for i in range(len(nums)):  # 枚举要删除的下标 i
            ans = max(ans, calc(nums[:i] + nums[i + 1 :]))  # 用删除 i 后数组的有效分割数更新答案
        return ans  # 返回最大有效分割位置个数
