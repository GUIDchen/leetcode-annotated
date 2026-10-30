# 题目：3512. 使数组和能被 K 整除的最少操作次数（Minimum Operations to Make Array Sum Divisible by K）
# 思路：一次操作可以把任意元素减 1，等价于把数组总和减 1。要让总和能被 k 整除，只需把总和减去它对 k 的余数，因此答案就是 sum(nums) % k。
# 时间复杂度：O(n)，累加求一遍和；空间复杂度：O(1)，只用了一个临时结果。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # nums：数组；k：除数；返回使数组和能被 k 整除的最少操作次数
        return sum(nums) % k  # 每次操作等价于把总和减 1，故只需减去总和模 k 的余数
