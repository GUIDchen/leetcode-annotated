# 3848. 阶数数字排列 / Check Digitorial Permutation（中等）
# 核心思路：用带缓存的递归求 0~9 的阶乘，求 n 各位数字阶乘之和，再比较其数字多重集与 n 是否相同。
# 复杂度：时间 O(log n)，空间 O(1)。
@cache  # 缓存阶乘结果，避免重复递归
def f(x: int) -> int:  # 计算 x 的阶乘
    if x < 2:  # 0! 与 1! 都为 1，作为递归出口
        return 1  # 递归出口返回值
    return x * f(x - 1)  # 递归计算 x!


class Solution:  # 题解类（LeetCode 约定类名）
    def isDigitorialPermutation(self, n: int) -> bool:  # 判断 n 与它各位数字的阶乘之和是否互为数字排列
        x, y = 0, n  # x 累加各位阶乘；y 是 n 的副本，用于逐位拆解
        while y:  # 逐位取出 n 的十进制数字
            x += f(y % 10)  # 加上当前最低位的阶乘
            y //= 10  # 去掉最低位
        return sorted(str(x)) == sorted(str(n))  # 排序后字符串相同即互为数字排列
