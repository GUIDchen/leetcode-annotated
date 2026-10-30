# 题目：1589. 所有排列中的最大和（Maximum Sum Obtained of Any Permutation）
# 思路：用差分数组统计每个下标被多少个区间覆盖，再把最大的数与最大的覆盖次数配对，即得最大和。
# 时间复杂度：O(n log n)，两处排序主导；空间复杂度：O(n)，差分数组。
class Solution:  # LeetCode 约定的题解类
    def maxSumRangeQuery(self, nums: List[int], requests: List[List[int]]) -> int:  # nums 可任意重排，requests 为查询区间
        n = len(nums)  # 数组长度
        d = [0] * n  # 差分数组，用来累计每个下标的覆盖次数
        for l, r in requests:  # 遍历每个查询区间
            d[l] += 1  # 区间起点处覆盖次数 +1
            if r + 1 < n:  # 右端点后一位仍在数组内时才抵消
                d[r + 1] -= 1  # 区间结束后取消覆盖
        for i in range(1, n):  # 前缀和还原出真实覆盖次数
            d[i] += d[i - 1]  # 累加前一位
        nums.sort()  # 数值升序
        d.sort()  # 覆盖次数升序
        mod = 10**9 + 7  # 取模常量
        return sum(a * b for a, b in zip(nums, d)) % mod  # 排序后同序相乘求和，即最大和
