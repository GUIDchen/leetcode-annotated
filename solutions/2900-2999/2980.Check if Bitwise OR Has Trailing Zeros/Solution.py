# 题目：2980. 检查按位或是否存在尾随零（Check if Bitwise OR Has Trailing Zeros）
# 思路：按位或结果的最低位只取决于各数的最低位，只要数组里至少有两个偶数，取它们相或最低位就是 0，即结果含尾随零。
# 时间复杂度：O(n)，扫一遍数组；空间复杂度：O(1)，只用常数级额外空间。
class Solution:  # LeetCode 约定的题解类
    def hasTrailingZeros(self, nums: List[int]) -> bool:  # nums：候选整数数组
        return sum(x & 1 ^ 1 for x in nums) >= 2  # x & 1 ^ 1 中 & 优先级高于 ^，偶数得 1、奇数得 0，求和即偶数个数；至少两个偶数即可
