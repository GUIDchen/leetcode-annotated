# 题目：3982. Sum of Integers with Maximum Digit Range（3982. 最大数字范围的整数之和）
# 核心思路：逐个整数拆位求出「最大数位 - 最小数位」，维护全局最大数位差；数位差更大则重置答案，并列最大则累加该数。
# 复杂度：时间 O(n·log10 V)（V 为数值大小，每个数要拆位），空间 O(1)。
class Solution:  # 定义题解类
    def maxDigitRange(self, nums: list[int]) -> int:  # 返回数位差最大的所有整数之和
        ans = mx = 0  # ans 存和，mx 存当前最大数位差
        for x in nums:  # 依次枚举每个整数
            a, b = 10, 0  # a 为最小数位初值 10，b 为最大数位初值 0
            y = x  # y 是拆位用的临时变量
            while y:  # 逐位取出，直到 y 变成 0
                v = y % 10  # v 是当前最低位上的数字
                y //= 10  # 去掉已经处理过的最低位
                a = min(a, v)  # 用当前位更新最小数位
                b = max(b, v)  # 用当前位更新最大数位
            r = b - a  # r 为该整数的数位差 = 最大数位 - 最小数位
            if mx < r:  # 出现了更大的数位差
                mx = r  # 更新全局最大数位差
                ans = x  # 答案重置为当前整数
            elif mx == r:  # 数位差与当前最大值并列
                ans += x  # 把当前整数累加进答案
        return ans  # 返回所有最大数位差的整数之和
