# 题目：2099. 找到和最大的长度为 K 的子序列（Find Subsequence of Length K With the Largest Sum）
# 思路：对所有下标按 nums 的值升序排序，取最后 k 个下标（即值最大的 k 个），再按原下标顺序输出对应元素。
# 时间复杂度：O(n log n)，排序开销；空间复杂度：O(n)，下标列表与答案列表。
class Solution:  # LeetCode 约定的题解类
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:  # nums 是输入数组，k 是子序列长度
        idx = sorted(range(len(nums)), key=lambda i: nums[i])[-k:]  # 按 nums 的值升序排下标，取末尾 k 个；sorted 再排一次把它们恢复成原数组顺序
        return [nums[i] for i in sorted(idx)]  # 按原下标顺序把这 k 个元素取出来作为答案
