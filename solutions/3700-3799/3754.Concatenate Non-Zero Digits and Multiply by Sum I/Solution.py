# 3754. 连接非零数字并乘以其数字和 I（Concatenate Non-Zero Digits and Multiply by Sum I）
# 核心思路：从低位到高位取出每一位数字，跳过 0，用权值 p 把非零数字依次拼成新数 x，同时累加数字和 s，最后返回 x * s。
# 复杂度：时间 O(log n)（n 的位数），空间 O(1)。
class Solution:  # 定义解法类
    def sumAndMultiply(self, n: int) -> int:  # 接口：返回把 n 的非零数字拼成的数乘以数字和
        p = 1  # p 为当前拼接位的权值（个位是 1，逐位乘 10）
        x = s = 0  # x 保存拼接出的数，s 保存各数字之和
        while n:  # 只要 n 还没有被除尽就继续循环
            n, v = divmod(n, 10)  # 同时取出最低位 v，并把 n 右移一位
            if v:  # 只处理非零数字
                s += v  # 累加数字和
                x += p * v  # 把 v 放到权值 p 对应的拼接位上
                p *= 10  # 权值扩大 10 倍，留给下一个非零数字
        return x * s  # 返回拼接数与数字和之积
