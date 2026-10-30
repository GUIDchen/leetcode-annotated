# 题目：3945. 计算数字频率得分（Digit Frequency Score）
# 思路：用 divmod(n, 10) 一次拿到商和余数，余数就是当前个位，累加到答案，直到 n 变成 0。
# 复杂度：时间 O(log n)（十进制位数），空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def digitFrequencyScore(self, n: int) -> int:  # n：待处理的正整数，返回它十进制各位数字之和
        ans = 0  # ans 累加每一位上的数字
        while n:  # 只要 n 仍大于 0 就继续拆位
            n, x = divmod(n, 10)  # 一次除法同时得到：n 去掉最低位，x 是最低位数字
            ans += x  # 把这一位累加进答案
        return ans  # 返回所有数位之和
