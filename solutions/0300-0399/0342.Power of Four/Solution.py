# 题目：342. 4的幂（Power of Four）
# 思路：判断 n 是正数、是 2 的幂（n & (n-1) == 0），并且那个唯一的 1 位于偶数位（用 0xAAAAAAAA 掩掉奇数位后为 0）。
# 时间复杂度：O(1)，只做几次位运算；空间复杂度：O(1)，只用常数个临时变量。
class Solution:  # LeetCode 约定的题解类
    def isPowerOfFour(self, n: int) -> bool:  # n：待判断的整数；返回布尔值表示是否为 4 的幂
        return n > 0 and (n & (n - 1)) == 0 and (n & 0xAAAAAAAA) == 0  # n > 0 先排除走非正数；n & (n-1) == 0 判断二进制只有一个 1；n & 0xAAAAAAAA == 0 判断这个 1 在偶数位
