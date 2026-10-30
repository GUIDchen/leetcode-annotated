# 题目：3254. 长度为 K 的子数组的能量值 I（Find the Power of K-Size Subarrays I）
# 思路：先预处理 f[i] 表示以 i 结尾的「连续递增 1」的最长长度，再对每个长度为 k 的窗口看右端 f[i] 是否达到 k，达到则能量值为 nums[i]，否则为 -1。
# 时间复杂度：O(n)，只需两趟线性扫描；空间复杂度：O(n)，用于存放 f 数组与答案列表。
class Solution:  # LeetCode 约定的题解类
    def resultsArray(self, nums: List[int], k: int) -> List[int]:  # nums：输入数组；k：子数组长度；返回每个窗口的能量值
        n = len(nums)  # n：数组长度
        f = [1] * n  # f[i]：以 i 结尾的「连续递增 1」的最大长度，初值 1
        for i in range(1, n):  # 从左到右递推每个位置
            if nums[i] == nums[i - 1] + 1:  # 刚好比前一个数大 1，说明可以接在上一个连续段后面
                f[i] = f[i - 1] + 1  # 连续长度在上一项基础上加 1
        return [nums[i] if f[i] >= k else -1 for i in range(k - 1, n)]  # 窗口右端 i 从 k-1 到 n-1，连续长度够 k 时取 nums[i]，否则取 -1
