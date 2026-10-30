# 题目：3345. 最小可整除数位乘积 I（Smallest Divisible Digit Product I）
# 思路：用 itertools.count 从 n 开始生成无穷递增序列，逐个校验数位乘积能否被 t 整除。
# 时间复杂度：O(答案 - n) 次校验，每次 O(位数)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def smallestNumber(self, n: int, t: int) -> int:  # n：枚举起点；t：数位乘积必须能被它整除
        for i in count(n):  # itertools.count(n) 生成 n, n+1, n+2, ... 的无界序列
            p = 1  # 数位乘积，乘法单位元取 1
            x = i  # 用副本 x 逐位剥离，保住原数 i
            while x:  # x 还有数位就继续拆
                p *= x % 10  # 取最低位乘进乘积
                x //= 10  # 整除 10 去掉最低位
            if p % t == 0:  # 数位乘积能被 t 整除
                return i  # 从小到大枚举，第一个命中的就是最小答案
