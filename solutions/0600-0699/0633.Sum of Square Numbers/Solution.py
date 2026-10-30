# 题目：633. 平方数之和（Sum of Square Numbers）
# 思路：双指针夹逼：a 从 0 递增、b 从 floor(sqrt(c)) 递减，平方和偏小就增大 a，偏大就减小 b。
# 时间复杂度：O(sqrt c)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def judgeSquareSum(self, c: int) -> bool:  # 判断 c 能否写成 a^2 + b^2（a、b 为非负整数）
        a, b = 0, int(sqrt(c))  # 左指针取 0，右指针取 floor(sqrt(c))；sqrt 由判题环境提供
        while a <= b:  # 两指针相遇即停止
            s = a**2 + b**2  # 当前两数的平方和；Python 大整数不会溢出，无需扩容
            if s == c:  # 正好等于 c
                return True  # 返回 True
            if s < c:  # 平方和偏小，需要增大 a
                a += 1  # 左指针右移
            else:  # 否则平方和偏大，需要减小 b
                b -= 1  # 右指针左移
        return False  # 尝试完所有组合仍无解，返回 False
