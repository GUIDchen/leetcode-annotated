# 题目：1611. 使整数变为 0 的最少操作次数（Minimum One Bit Operations to Make Integers Zero）
# 思路：题目操作对应格雷码的相邻转换，最少次数为 n ^ (n>>1) ^ (n>>2) ^ …，逐位异或即可。
# 时间复杂度：O(log n)，每位一次；空间复杂度：O(1)。
class Solution:  # 题解类
    def minimumOneBitOperations(self, n: int) -> int:  # 输入 n，返回把它变成 0 所需的最少操作次数
        ans = 0  # 答案累加器
        while n:  # 逐位处理，直到 n 变成 0
            ans ^= n  # 把当前 n 异或进答案：答案等于 n、n>>1、n>>2… 的异或和（格雷码逆变换）
            n >>= 1  # n 右移一位，处理下一位
        return ans  # 返回最少操作次数
