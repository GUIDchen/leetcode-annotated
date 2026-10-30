# 题目：136. 只出现一次的数字（Single Number）
# 思路：reduce 把 xor 依次作用到整个数组上，利用 a ^ a = 0、a ^ 0 = a，成对出现的数抵消后只剩单独的那个。
# 时间复杂度：O(n)，只需一次线性归约；空间复杂度：O(1)，除结果外不用额外空间。
class Solution:  # LeetCode 约定的题解类
    def singleNumber(self, nums: List[int]) -> int:  # 返回唯一出现一次的元素
        return reduce(xor, nums)  # reduce(xor, nums) 把全部元素从左到右异或起来，成对的自动抵消
