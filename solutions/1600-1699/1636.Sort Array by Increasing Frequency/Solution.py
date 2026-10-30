# 题目：1636. 按照频率将数组升序排序（Sort Array by Increasing Frequency）
# 思路：先统计每个值的出现次数，再按「频率升序、频率相同则值降序」的规则重排数组。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，Counter 存不同值的频次。
class Solution:  # LeetCode 约定的题解类
    def frequencySort(self, nums: List[int]) -> List[int]:  # nums 是输入数组，返回按频率升序（同频时值降序）排好的数组
        cnt = Counter(nums)  # 统计每个值的出现次数（值为键，频次为值）
        return sorted(nums, key=lambda x: (cnt[x], -x))  # 排序键是二元组 (频次, -值)：频次升序，频次相同时值大的（-x 小的）靠前
