# 题目：1099. 小于 K 的两数之和（Two Sum Less Than K）
# 思路：排序后枚举较小的数 x，二分出最后一个满足 nums[j] < k - x 的下标 j，取最大的 x + nums[j]。
# 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(1)，只用常数个变量（排序自身不计）。
class Solution:  # LeetCode 约定的题解类
    def twoSumLessThanK(self, nums: List[int], k: int) -> int:  # nums 是候选数组，k 是两数之和的上界（严格小于）
        nums.sort()  # 原地排序，为二分创造单调性
        ans = -1  # 答案初始为 -1，表示不存在合法数对
        for i, x in enumerate(nums):  # 枚举较小的数 x 及其下标 i
            j = bisect_left(nums, k - x, lo=i + 1) - 1  # 在 i 右侧二分找最后一个小于 k - x 的下标：bisect_left 返回第一个 >= 的位置，再减 1
            if i < j:  # j 要严格在 i 右侧，避免重复使用同一个元素
                ans = max(ans, x + nums[j])  # 更新最大和
        return ans  # 返回答案，没有合法数对时仍是 -1
