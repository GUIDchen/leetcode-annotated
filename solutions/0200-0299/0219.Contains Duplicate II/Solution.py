# 题目：219. 存在重复元素 II（Contains Duplicate II）
# 核心思路：哈希表记录每个值最近一次出现的下标，扫描时比较当前下标与最近下标的差是否不超过 k。
# 时间复杂度：O(n)，每个元素只查表一次；空间复杂度：O(n)，哈希表最多存 n 个不同值。
class Solution:  # LeetCode 约定的题解类
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:  # 判断是否存在两个相等元素，其下标差不超过 k
        d = {}  # 哈希表：键是元素值，值是它最近一次出现的下标
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            if x in d and i - d[x] <= k:  # 该值之前出现过，且下标差不超过 k
                return True  # 找到满足条件的重复对
            d[x] = i  # 更新为最新下标，让后续判断拿到最小的下标差
        return False  # 扫描完仍未找到
