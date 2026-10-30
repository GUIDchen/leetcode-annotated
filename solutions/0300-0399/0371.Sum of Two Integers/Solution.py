# 题目：371. 两整数之和（Sum of Two Integers）
# 思路：Py3 整数无溢出位宽，先截断到 32 位无符号，用 a ^ b 求无进位和、(a & b) << 1 求进位，循环到进位为 0 后再按符号还原。
# 时间复杂度：O(log n)，进位最多循环约 32 轮；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def getSum(self, a: int, b: int) -> int:  # a、b 是待相加的两个整数，可为负数；要求不使用 + - 运算符
        a, b = a & 0xFFFFFFFF, b & 0xFFFFFFFF  # 统一截断成 32 位无符号表示，模拟补码机器上的位运算
        while b:  # 进位不为 0 就继续迭代
            carry = ((a & b) << 1) & 0xFFFFFFFF  # 进位：同为 1 的位左移一位，再截断回 32 位
            a, b = a ^ b, carry  # 同时更新：无进位和 与 进位
        return a if a < 0x80000000 else ~(a ^ 0xFFFFFFFF)  # 最高位为 1 说明是负数，按 32 位补码规则还原成 Python 的负整数
