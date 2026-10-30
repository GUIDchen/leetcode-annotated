# 题目：190. 颠倒二进制位（Reverse Bits）
# 思路：逐位取出最低位，放到结果 ans 的对称高位（第 31-i 位），再把 n 右移一位。
# 时间复杂度：O(1)，固定循环 32 次；空间复杂度：O(1)，只用两个整数变量。
class Solution:  # LeetCode 约定的题解类
    def reverseBits(self, n: int) -> int:  # n 是 32 位无符号整数（Python 里就是普通 int）
        ans = 0  # 结果累加器，初始为 0
        for i in range(32):  # 固定遍历 32 个二进制位
            ans |= (n & 1) << (31 - i)  # 取 n 的最低位，左移到第 31-i 位后按位或进 ans
            n >>= 1  # n 无符号右移一位，把下一位挪到最低位
        return ans  # 返回颠倒后的 32 位整数
