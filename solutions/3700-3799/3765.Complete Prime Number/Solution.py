# 3765. 完全质数 / Complete Prime Number
# 核心思路：把 num 转成十进制字符串，分别枚举它的所有前缀与所有后缀，逐个做质数判定。
# 复杂度：时间 O(d·√num)（d 为十进制位数），空间 O(d)。
class Solution:  # 定义解法类
    def completePrime(self, num: int) -> bool:  # 判断 num 的所有十进制前缀和所有十进制后缀是否都是质数
        def is_prime(x: int) -> bool:  # 质数判定函数
            if x < 2:  # 小于 2 的数不是质数
                return False  # 返回 False
            return all(x % i for i in range(2, int(sqrt(x)) + 1))  # 用 all() 试除 2 到 √x，无因子即为质数

        s = str(num)  # 转成十进制字符串
        x = 0  # 前缀的累加值
        for c in s:  # 从左到右遍历每一位
            x = x * 10 + int(c)  # 拼出当前前缀数值
            if not is_prime(x):  # 前缀不是质数则整体失败
                return False  # 返回 False
        x, p = 0, 1  # 后缀的累加值与位权
        for c in s[::-1]:  # 从右到左遍历每一位
            x = p * int(c) + x  # 把该位拼到当前后缀的最前面
            p *= 10  # 位权乘 10
            if not is_prime(x):  # 后缀不是质数则整体失败
                return False  # 返回 False
        return True  # 所有前缀和后缀都是质数
