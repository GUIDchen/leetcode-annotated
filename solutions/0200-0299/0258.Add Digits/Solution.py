# 题目：258. 各位相加（Add Digits）
# 思路：数根公式。反复各位相加的最终结果等于 n mod 9（余 0 时取 9），即 (n-1) % 9 + 1，可一步算出。
# 时间复杂度：O(1)；空间复杂度：O(1)。

class Solution:  # LeetCode 约定的题解类
    def addDigits(self, num: int) -> int:  # num：非负整数输入
        return 0 if num == 0 else (num - 1) % 9 + 1  # num 为 0 时数根是 0（公式会把 0 算成 9，需单独处理），否则套用公式
