# 题目：1780. 判断一个数字是否可以表示成三的幂的和（Check if Number is a Sum of Powers of Three）
# 思路：把 n 看成三进制，题目要求每个三的幂最多用一次，等价于三进制每一位只能是 0 或 1。
# 时间复杂度：O(log n)，每次除以 3；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def checkPowersOfThree(self, n: int) -> bool:  # n 是待判断的正整数
        while n:  # 不断取出三进制的最低位，直到 n 被除尽
            if n % 3 > 1:  # 三进制某一位是 2，说明该幂需要重复使用
                return False  # 无法表示成互不相同的三的幂之和
            n //= 3  # 整体右移一位（整除 3），继续看下一位
        return True  # 所有位都只出现 0 或 1，可以表示
