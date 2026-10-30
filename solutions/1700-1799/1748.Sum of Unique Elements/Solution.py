# 题目：1748. 唯一元素的和（Sum of Unique Elements）
# 核心思路：用 Counter 一次性统计每个元素的出现次数，再用生成器表达式把所有出现次数为 1 的元素值加起来。
# 时间复杂度：O(n)，统计与求和各遍历一次；空间复杂度：O(n)，Counter 最多保存 n 个不同取值。
class Solution:  # LeetCode 约定的题解类
    def sumOfUnique(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有只出现一次的元素之和
        cnt = Counter(nums)  # 一次性统计每个元素出现的次数：键是元素值，值是次数
        return sum(x for x, v in cnt.items() if v == 1)  # 只挑出现次数恰好为 1 的元素值求和
