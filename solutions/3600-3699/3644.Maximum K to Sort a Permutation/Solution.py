# 题目：3644. 排序排列（Maximum K to Sort a Permutation）
# 核心思路：已经就位的下标不受 k 影响；每个错位元素 x 都会在 x & k 中丢掉 k 为 0 的二进制位，要让它恰好落到下标 i，k 只能保留所有错位元素共有的位，于是把所有错位元素按位与起来，结果再与 0 取较大值即可。
# 复杂度：时间 O(n)，一次遍历；空间 O(1)，只用了一个整型变量。
class Solution:  # LeetCode 题解类
    def sortPermutation(self, nums: List[int]) -> int:  # nums：长度为 n 的排列；返回能完成排序的最大 k
        ans = -1  # 用全 1 的位掩码做起点，逐位与错位元素取与
        for i, x in enumerate(nums):  # 遍历每个下标 i 与对应元素 x
            if i != x:  # 该位置本来就有序，不受 k 的位影响
                ans &= x  # 错位元素只能保留各元素共有的 1 位
        return max(ans, 0)  # 没有错位元素时结果为 0（不能为负）
