# 题目：3712. Sum of Elements With Frequency Divisible by K（3712. 出现次数能被 K 整除的元素总和）
# 核心思路：先用 Counter 统计每个元素的出现次数，再用生成器表达式把出现次数能被 k 整除的元素按“值 × 次数”累加。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # LeetCode 约定的题解类
    def sumDivisibleByK(self, nums: List[int], k: int) -> int:  # 返回出现次数能被 k 整除的元素总和
        cnt = Counter(nums)  # 统计每个元素的出现次数
        return sum(x * v for x, v in cnt.items() if v % k == 0)  # 只累加出现次数能被 k 整除的元素，贡献为 值 × 次数
