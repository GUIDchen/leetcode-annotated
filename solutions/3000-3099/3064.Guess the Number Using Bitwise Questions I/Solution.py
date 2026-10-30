# 题目：3064. 使用按位查询猜测数字 I（Guess the Number Using Bitwise Questions I）
# 思路：逐位构造答案；掩码只保留第 i 位，commonSetBits 返回非零就说明隐藏数字该位为 1，把该位累加进结果。
# 时间复杂度：O(32)=O(1)，最多查询 32 次；空间复杂度：O(1)，只用一个整数累积答案。
# Definition of commonSetBits API.
# def commonSetBits(num: int) -> int:


class Solution:  # LeetCode 约定的题解类
    def findNumber(self) -> int:  # 无需入参，返回猜出的隐藏数字
        return sum(1 << i for i in range(32) if commonSetBits(1 << i))  # 生成器依次试探 32 个二进制位，为真时把 1 << i 计入总和，等价于逐位或
