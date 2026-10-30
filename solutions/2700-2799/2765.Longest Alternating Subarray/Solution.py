# 题目：2765. 最长交替子数组（Longest Alternating Subarray）
# 思路：枚举起点 i，用 k 表示期望的相邻差值（1 与 -1 交替），while 循环尽量向右扩展，记录长度至少为 2 的最大值。
# 时间复杂度：O(n^2)，最坏情况每个起点都扫到尾部；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def alternatingSubarray(self, nums: List[int]) -> int:  # nums 是输入数组，返回最长交替子数组的长度
        ans, n = -1, len(nums)  # ans 初始为 -1 表示还没有合法子数组；n 是数组长度
        for i in range(n):  # 枚举交替子数组的起点 i
            k = 1  # 期望的相邻差值，初始要求 nums[j+1] - nums[j] == 1
            j = i  # 当前子数组的右端点，先把 j 指向起点
            while j + 1 < n and nums[j + 1] - nums[j] == k:  # 只要右边还有元素且差值恰好为 k，就继续向右扩展
                j += 1  # 右端点右移一位
                k *= -1  # 差值要求翻转：1 → -1 → 1，保证「大、小、大」交替
            if j - i + 1 > 1:  # 长度至少为 2 才算合法的交替子数组
                ans = max(ans, j - i + 1)  # 用当前长度更新历史最大值
        return ans  # 一个合法子数组都没有时 ans 保持 -1，符合题目要求
