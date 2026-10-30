# 题目：1979. 找出数组的最大公约数（Find Greatest Common Divisor of Array）
# 思路：数组的最大值与最小值一定都在数组中，答案就是这两个数的最大公约数，取极值后直接求 gcd。
# 时间复杂度：O(n)，一次遍历取极值；空间复杂度：O(1)，只用两个临时值。
class Solution:  # LeetCode 约定的题解类
    def findGCD(self, nums: List[int]) -> int:  # nums 是输入数组，返回其最大值与最小值的最大公约数（gcd 由判题器隐式导入）
        return gcd(max(nums), min(nums))  # 先取最大值和最小值，再求两者的最大公约数即为答案
