# 题目：2544. 交替数字和（Alternating Digit Sum）
# 思路：把 n 转成字符串，用生成器按奇偶下标交替乘 +1/-1 后求和，一行完成。
# 时间复杂度：O(log n)，即位数；空间复杂度：O(log n)，字符串占用的临时空间。
class Solution:  # LeetCode 约定的题解类
    def alternateDigitSum(self, n: int) -> int:  # 返回从最高位开始正负交替的数字和
        return sum((-1) ** i * int(x) for i, x in enumerate(str(n)))  # enumerate 给出下标 i 与字符 x；偶下标取正、奇下标取负，求和即答案
