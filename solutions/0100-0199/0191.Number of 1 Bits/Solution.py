# 题目：191. 位1的个数（Number of 1 Bits）
# 思路：n &= n - 1 每次消掉最低位的一个 1，循环次数就等于 1 的个数。
# 时间复杂度：O(1)，最多 32 次循环；空间复杂度：O(1)，只用两个整数变量。
class Solution:  # LeetCode 约定的题解类
    def hammingWeight(self, n: int) -> int:  # n 是 32 位无符号整数，返回其中 1 的个数
        ans = 0  # 计数器
        while n:  # n 不为 0 就继续，循环次数等于 1 的个数
            n &= n - 1  # 把最低位的 1 清零
            ans += 1  # 计数加一
        return ans  # 返回 1 的总个数
