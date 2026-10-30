# 题目：1837. K 进制表示下的各位数字总和（Sum of Digits in Base K）
# 思路：反复对 k 取余得到最低位数字并累加，再整除 k 去掉这一位，直到 n 归零。
# 时间复杂度：O(log_k n)，即 k 进制下的位数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def sumBase(self, n: int, k: int) -> int:  # n 是待转换的十进制数，k 是目标进制，返回其 k 进制表示的各位数字之和
        ans = 0  # 累加各位数字之和
        while n:  # n 还非零说明还有高位没拆完
            ans += n % k  # 取 n 在 k 进制下的最低位数字并累加
            n //= k  # 整除 k 去掉已处理的最低位，相当于右移一位 k 进制
        return ans  # 返回各位数字总和
