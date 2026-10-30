# 题目：3513. 不同 XOR 三元组的数目 I（Number of Unique XOR Triplets I）
# 思路：结论题——长度 n <= 2 时不同异或值是 n 个；n >= 3 时答案是 2 的「n 的二进制位数」次方。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def uniqueXorTriplets(self, nums: List[int]) -> int:  # nums：输入的整数数组，返回不同异或三元组的个数
        n = len(nums)  # n：数组长度
        return n if n <= 2 else 1 << n.bit_length()  # 长度不超过 2 时答案为 n；否则为 1 左移 n.bit_length() 位
