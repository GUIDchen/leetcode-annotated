# 题目：1680. 连接连续二进制数字（Concatenation of Consecutive Binary Numbers）
# 思路：从左到右增量拼接；i 的二进制位数用 i.bit_length() 取得，把当前结果左移这么多位后再按位或上 i，最后取模。
# 时间复杂度：O(n)，每个 i 只做常数次位运算；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def concatenatedBinary(self, n: int) -> int:  # 把 1 到 n 的二进制串首尾相接，返回对 1e9+7 取模后的值
        mod = 10**9 + 7  # 题目要求的取模数
        ans = 0  # ans 保存当前拼接结果；Python 大整数不会溢出
        for i in range(1, n + 1):  # 依次把 1 到 n 的二进制串拼到已有结果后面
            ans = (ans << i.bit_length() | i) % mod  # bit_length 给出 i 的二进制位数：左移腾出低位，再按位或上 i，最后取模
        return ans  # 返回拼接结果
