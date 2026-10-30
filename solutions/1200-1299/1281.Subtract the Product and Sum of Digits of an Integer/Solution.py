# 题目：1281. 整数的各位积和之差（Subtract the Product and Sum of Digits of an Integer）
# 思路：每轮用 divmod 同时拿到商与最低位，商继续循环，最低位分别乘入积、加入和，最后积减和。
# 时间复杂度：O(log n)，循环次数等于十进制位数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def subtractProductAndSum(self, n: int) -> int:  # 输入整数 n，返回各位数字之积减去各位数字之和
        x, y = 1, 0  # x 是各位数字的乘积（初始 1），y 是各位数字之和（初始 0）
        while n:  # n 非 0 就继续，等价于 while n > 0
            n, v = divmod(n, 10)  # 一次性得到商 n 与最低位数字 v
            x *= v  # 把这一位乘入积中
            y += v  # 把这一位加入和中
        return x - y  # 返回各位数字之积与各位数字之和的差
