# 题目：507. 完美数（Perfect Number）
# 思路：1 一定是真因子先计入；从 2 枚举到 sqrt(num)，遇到因子就成对累加 i 与 num//i，最后判断因子和是否等于自身。
# 时间复杂度：O(sqrt(num))；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def checkPerfectNumber(self, num: int) -> bool:  # num：待判断的正整数
        if num == 1:  # 1 没有真因子，不可能是完美数
            return False  # 直接返回 False
        s, i = 1, 2  # s 累计真因子之和（1 先计入），i 从 2 开始枚举
        while i <= num // i:  # 只枚举到 sqrt(num)，用整除避免浮点误差
            if num % i == 0:  # i 是 num 的因子
                s += i  # 累加较小的因子 i
                if i != num // i:  # 配对因子与 i 不相等时才累加，避免平方数重复计算
                    s += num // i  # 累加较大的配对因子 num // i
            i += 1  # 枚举下一个候选因子
        return s == num  # 真因子之和等于自身即为完美数
