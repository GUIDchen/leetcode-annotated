# 题目：1712. 将数组分成三个子数组的方案数（Ways to Split Array Into Three Subarrays）
# 思路：先求前缀和，枚举第一刀位置 i；数组非负所以前缀和单调，第二刀位置的合法集合是一段连续下标，用 bisect_left 取下界、bisect_right 取上界，长度即为该 i 的方案数。
# 时间复杂度：O(n log n)，每个 i 做两次二分；空间复杂度：O(n)，前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def waysToSplit(self, nums: List[int]) -> int:  # nums 是非负整数数组，要切成三个非空连续子数组
        mod = 10**9 + 7  # 结果取模的常数
        s = list(accumulate(nums))  # 前缀和数组：s[i] 表示 nums[0..i] 的和
        ans, n = 0, len(nums)  # ans 累计方案数，n 是数组长度
        for i in range(n - 2):  # 枚举第一刀位置 i，后面两段至少各留一个元素，故 i 最多到 n-3
            j = bisect_left(s, s[i] << 1, i + 1, n - 1)  # 第二刀最早位置：使第二段和 s[j]-s[i] >= 第一段和 s[i]，即在 [i+1, n-2) 内找第一个 s[j] >= 2*s[i]
            k = bisect_right(s, (s[-1] + s[i]) >> 1, j, n - 1)  # 第二刀最晚位置的后一位：使第三段和 >= 第二段和，即在 [j, n-2) 内找最后一个 s[k] <= (总和+s[i])/2
            ans += k - j  # [j, k) 内每个第二刀位置都合法，累加方案数
        return ans % mod  # 对方案总数取模后返回
