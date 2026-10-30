# 题目：2760. 最长奇偶子数组（Longest Even Odd Subarray With Threshold）
# 思路：枚举左端点，只在 nums[l] 是偶数且不超过 threshold 时向右扩展；扩展条件是与前一个元素奇偶性不同且值不超过 threshold，用 r - l 更新答案。
# 时间复杂度：O(n^2)，最坏情况每个左端点都要向右扫一遍；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def longestAlternatingSubarray(self, nums: List[int], threshold: int) -> int:  # nums 是输入数组，threshold 是元素允许的最大值
        ans, n = 0, len(nums)  # ans 记录答案长度，n 是数组长度（元组赋值一次算好两个变量）
        for l in range(n):  # 枚举子数组的左端点 l
            if nums[l] % 2 == 0 and nums[l] <= threshold:  # 合法子数组必须从偶数开始，而且这个偶数不能超过 threshold
                r = l + 1  # 右端点从 l + 1 开始，因为 l 本身已经是一个合法子数组
                while r < n and nums[r] % 2 != nums[r - 1] % 2 and nums[r] <= threshold:  # 向右扩展：不越界、与前一个元素奇偶性交替、且值不超过 threshold
                    r += 1  # 条件全部满足，右端点右移一位
                ans = max(ans, r - l)  # r - l 就是以 l 开头的最长奇偶交替子数组长度
        return ans  # 返回最长长度，没有合法子数组时返回 0
