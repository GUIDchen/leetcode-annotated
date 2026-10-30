# 3866. 找到第一个唯一偶数 / First Unique Even Element
# 核心思路：用 Counter 统计每个值的出现次数，再按原顺序扫描，返回第一个“出现一次且为偶数”的元素。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(V)，V 为不同值的个数。
class Solution:  # LeetCode 题解类
    def firstUniqueEven(self, nums: list[int]) -> int:  # 返回第一个只出现一次的偶数，不存在则返回 -1
        cnt = Counter(nums)  # 统计每个值的出现次数
        for x in nums:  # 按原数组顺序扫描
            if x % 2 == 0 and cnt[x] == 1:  # 既是偶数，又只出现过一次
                return x  # 立即返回该唯一偶数
        return -1  # 不存在唯一偶数，返回 -1
