# 题目：2997. 使数组异或和等于 K 的最少操作次数（Minimum Number of Operations to Make Array XOR Equal to K）
# 核心思路：以 k 为初值对所有元素做异或，得到「当前异或和 ⊕ 目标值」，其中每个为 1 的二进制位都需要一次翻转操作。
# 时间复杂度：O(n)，一次归约加一次 bit_count；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是目标异或值
        return reduce(xor, nums, k).bit_count()  # 以 k 为初值求整体异或，再数出其中 1 的个数，即最少操作次数
