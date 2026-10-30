# 题目：3099. 哈沙德数（Harshad Number）
# 思路：逐位取出数字累加得到数位和，再判断数位和能否整除原数：能整除就是哈沙德数。
# 时间复杂度：O(log x)，即十进制位数；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def sumOfTheDigitsOfHarshadNumber(self, x: int) -> int:  # x：待判断的整数，返回其数位和或 -1
        s, y = 0, x  # s 存数位和，y 是用于逐位取数的临时变量
        while y:  # y 还有剩余数位时继续循环
            s += y % 10  # 取当前末位累加进数位和
            y //= 10  # 去掉已经处理过的末位
        return s if x % s == 0 else -1  # 数位和能整除 x 就返回它，否则返回 -1
