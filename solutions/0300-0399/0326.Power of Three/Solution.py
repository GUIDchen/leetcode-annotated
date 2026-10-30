# 题目：326. 3 的幂（Power of Three）
# 思路：反复整除 3 缩小规模，过程中一旦出现不能被 3 整除的数就不是 3 的幂；除到 n<=2 后剩下的必须是 1。
# 时间复杂度：O(log n)，每次除以 3；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def isPowerOfThree(self, n: int) -> bool:  # n：待判断的整数，返回它是否为 3 的幂
        while n > 2:  # 只要 n 还大于 2 就继续缩小规模
            if n % 3:  # 余数非 0：当前数不能被 3 整除，必然不是 3 的幂
                return False  # 直接返回失败
            n //= 3  # 向下整除 3，规模缩小到三分之一
        return n == 1  # 除到底后剩下的正好是 1 才是 3 的幂
