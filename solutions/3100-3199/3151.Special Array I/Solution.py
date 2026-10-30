# 题目：3151. 特殊数组 I（Special Array I）
# 思路：用 pairwise 把数组拆成相邻二元组，再要求所有组内两端奇偶性都不同。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，pairwise 是惰性迭代器。
class Solution:  # LeetCode 约定的题解类
    def isArraySpecial(self, nums: List[int]) -> bool:  # nums 是输入数组，返回它是否为特殊数组
        return all(a % 2 != b % 2 for a, b in pairwise(nums))  # pairwise 惰性产出相邻二元组，all 检查每组奇偶性都不同
