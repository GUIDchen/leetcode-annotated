# 题目：866. 回文质数（Prime Palindrome）
# 思路：从 n 起逐个向上枚举，先用 reverse 判回文、再用试除法判质数；8 位回文数必是 11 的倍数，故跳过 [10^7, 10^8) 区间。
# 时间复杂度：O(枚举个数 × sqrt(当前值))；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def primePalindrome(self, n: int) -> int:  # 返回大于等于 n 的最小回文质数
        def is_prime(x):  # 内嵌函数：判断 x 是否为质数（试除法）
            if x < 2:  # 小于 2 的数不是质数
                return False  # 直接排除 0、1 和负数
            v = 2  # 从最小的质数 2 开始试除
            while v * v <= x:  # 只需试到 sqrt(x)，用乘法比较避免浮点开方
                if x % v == 0:  # 能整除说明存在因子，x 是合数
                    return False  # 立即返回 False
                v += 1  # 因子递增，继续试除
            return True  # 没有找到因子，x 是质数

        def reverse(x):  # 内嵌函数：把十进制数字反转，用于回文判断
            res = 0  # res 保存反转后的数值
            while x:  # 逐位处理，直到 x 变成 0
                res = res * 10 + x % 10  # 把 x 的末位接到 res 尾部
                x //= 10  # 用整除去掉末位（Python 的 // 向下取整，正数等价于整除）
            return res  # 返回反转结果

        while 1:  # 从小到大逐个枚举，命中即返回
            if reverse(n) == n and is_prime(n):  # 同时满足「是回文」和「是质数」才是答案
                return n  # 返回第一个满足条件的最小值
            if 10**7 < n < 10**8:  # 8 位回文数必是 11 的倍数，跳过整个 [10^7, 10^8) 区间
                n = 10**8  # 直接跳到 10^8，省去一千万次无意义的枚举
            n += 1  # 否则只把 n 加一，检查下一个数
