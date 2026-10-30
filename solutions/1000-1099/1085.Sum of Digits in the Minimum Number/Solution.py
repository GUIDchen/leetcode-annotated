# 题目：1085. 最小元素各数位之和（Sum of Digits in the Minimum Number）
# 思路：先取数组最小值，再在循环里不断「取个位、整除 10」累加数位和 s，最后按 s 的奇偶返回 1（偶数）或 0（奇数）。
# 时间复杂度：O(n + log x)，n 为数组长度，找最小值 O(n)、拆位 O(log x)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def sumOfDigits(self, nums: List[int]) -> int:  # nums 是给定的正整数数组
        x = min(nums)  # 找出整个数组的最小值
        s = 0  # 累加最小值的各数位之和
        while x:  # 只要 x 还没被除到 0 就继续拆位
            s += x % 10  # 取出当前最低位的数字并累加
            x //= 10  # 整除 10，去掉已经处理过的最低位
        return s & 1 ^ 1  # 先 s&1 取奇偶，再 ^1 取反：数位和为偶数返回 1、奇数返回 0
