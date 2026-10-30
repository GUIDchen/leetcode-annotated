# 题目：3162. 优质数对的总数 I（Find the Number of Good Pairs I）
# 思路：用双重生成器枚举所有数对 (x, y)，把 x % (y * k) == 0 的布尔值求和即得对数。
# 时间复杂度：O(n * m)，n、m 分别是两个数组的长度；空间复杂度：O(1)，只用了常数个临时变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfPairs(self, nums1: List[int], nums2: List[int], k: int) -> int:  # nums1、nums2 是输入数组，k 是题目给定的倍数；返回优质数对个数
        return sum(x % (y * k) == 0 for x in nums1 for y in nums2)  # 两层 for 依次枚举 x 与 y，布尔值 True/False 相加即满足条件的数对个数
