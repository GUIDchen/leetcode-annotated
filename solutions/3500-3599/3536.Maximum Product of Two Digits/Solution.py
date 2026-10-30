# 3536. 两个数字的最大乘积 / Maximum Product of Two Digits
# 核心思路：逐位取出每个数字，维护最大的两个位数字 a、b，最后返回 a * b。
# 复杂度：时间 O(log n)，空间 O(1)。
class Solution:  # 定义题解类
    def maxProduct(self, n: int) -> int:  # 返回 n 的各位数字中任取两位的最大乘积
        a = b = 0  # a 为最大位数字，b 为次大位数字
        while n:  # 逐位处理
            n, x = divmod(n, 10)  # 取最低位 x，同时去掉最低位
            if a < x:  # 比最大值还大
                a, b = x, a  # 原最大值降为次大值，x 成为最大值
            elif b < x:  # 否则比次大值大
                b = x  # 更新次大值
        return a * b  # 最大的两个位数字相乘
