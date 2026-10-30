# 题目：1134. 阿姆斯特朗数（Armstrong Number）
# 思路：先求出 n 的十进制位数 k，再逐位取出数字累加其 k 次方，最后判断该和是否等于 n 本身。
# 时间复杂度：O(log n)，需要遍历 n 的每一位；空间复杂度 O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def isArmstrong(self, n: int) -> bool:  # n：待判断的整数；返回它是否为阿姆斯特朗数
        k = len(str(n))  # k：n 的十进制位数，即每位要取的幂次
        s, x = 0, n  # s 为各位幂次之和，x 用于逐位剥离数字
        while x:  # 从最低位开始逐位处理
            s += (x % 10) ** k  # 累加当前最低位的 k 次方
            x //= 10  # 去掉已经处理过的最低位
        return s == n  # 各位幂次之和等于原数才是阿姆斯特朗数
