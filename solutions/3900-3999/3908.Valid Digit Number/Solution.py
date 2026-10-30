# 3908. 有效数字整数（Valid Digit Number）
# 思路：反复去掉最低位直到只剩最高位，过程中检查除最高位外是否出现过数字 x，最后要求最高位不等于 x。
# 复杂度：时间复杂度 O(log n)，空间复杂度 O(1)。
class Solution:  # LeetCode 约定的题解类
    def validDigit(self, n: int, x: int) -> bool:  # 判断 n 除最高位外是否含数字 x，且最高位不等于 x
        has_x = False  # 标记除最高位外是否出现过数字 x
        while n > 9:  # 不断去掉最低位，直到只剩最高位
            has_x = has_x or n % 10 == x  # 检查当前最低位是否为 x
            n //= 10  # 去掉最低位
        return has_x and n != x  # 低位出现过 x 且最高位不是 x 才算有效
