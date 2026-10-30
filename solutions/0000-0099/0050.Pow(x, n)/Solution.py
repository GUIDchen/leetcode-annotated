# 题目：50. Pow(x, n)（Pow(x, n)）
# 思路：快速幂。把指数按二进制拆成若干 2 的幂，逐位平方底数、按位累乘结果；负指数先取正算再取倒数。
# 时间复杂度：O(log |n|)，循环次数等于指数的二进制位数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def myPow(self, x: float, n: int) -> float:  # x 为底数，n 为整数指数（可能为负）
        def qpow(a: float, n: int) -> float:  # 内层快速幂：a 为底数，n 为非负指数
            ans = 1  # 累计结果，乘法单位元
            while n:  # 指数还没被消耗完就继续
                if n & 1:  # 指数最低位为 1，说明当前这个 a^(2^k) 要乘进结果
                    ans *= a  # 累乘当前幂
                a *= a  # 底数平方，准备下一位
                n >>= 1  # 指数右移一位，处理下一个二进制位
            return ans  # 返回 a^n

        return qpow(x, n) if n >= 0 else 1 / qpow(x, -n)  # n 非负直接算；n 为负则算正数次幂后取倒数（Python 整数无溢出问题）
