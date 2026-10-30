# 题目：3005. 最大频率元素计数（Count Elements With Maximum Frequency）
# 核心思路：用 Counter 统计每个元素出现次数，取出最大频次，再把所有等于最大频次的计数累加。
# 时间复杂度：O(n)，n 为数组长度；空间复杂度：O(n)，哈希表保存不同元素及其频次。
class Solution:  # LeetCode 约定的题解类
    def maxFrequencyElements(self, nums: List[int]) -> int:  # nums 是输入数组
        cnt = Counter(nums)  # Counter 直接统计每个元素的出现次数
        mx = max(cnt.values())  # 最大的出现次数
        return sum(x for x in cnt.values() if x == mx)  # 把所有出现次数等于最大值的项累加，就是答案
