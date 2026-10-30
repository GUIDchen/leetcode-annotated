# 题目：2425. 所有数对的异或和（Bitwise XOR of All Pairings）
# 核心思路：全部数对的异或和，等价于 nums1 每个元素重复 |nums2| 次、nums2 每个元素重复 |nums1| 次后再异或；同一元素异或偶数次抵消，故只在另一数组长度为奇数时异或它。
# 时间复杂度：O(n + m)，最多各遍历一次；空间复杂度：O(1)，只用一个累加变量。
class Solution:  # LeetCode 约定的题解类
    def xorAllNums(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 是两个输入数组，返回所有数对的异或和
        ans = 0  # 累加器：异或的单位元是 0
        if len(nums2) & 1:  # len(nums2) & 1 为真说明 nums2 长度为奇数
            for v in nums1:  # 遍历 nums1 的每个元素
                ans ^= v  # 异或累加，出现偶数次的元素会相互抵消
        if len(nums1) & 1:  # 同理判断 nums1 长度是否为奇数
            for v in nums2:  # 遍历 nums2 的每个元素
                ans ^= v  # 异或累加到答案
        return ans  # 返回所有数对的异或和
