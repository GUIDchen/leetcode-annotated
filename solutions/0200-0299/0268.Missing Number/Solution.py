# 题目：268. 丢失的数字（Missing Number）
# 思路：把 1..n 的下标与数组元素两两异或，成对的数抵消，剩下的就是缺失的数。
# 时间复杂度：O(n)；空间复杂度：O(1)，异或折叠不保存中间结果。
class Solution:  # LeetCode 约定的题解类
    def missingNumber(self, nums: List[int]) -> int:  # nums 是缺失了一个数、长度为 n 的 0..n 排列
        return reduce(xor, (i ^ v for i, v in enumerate(nums, 1)))  # enumerate 从 1 开始取下标，异或把成对的数抵消，剩下的即缺失值
