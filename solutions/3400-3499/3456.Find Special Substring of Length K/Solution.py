# 3456. 找出长度为 K 的特殊子字符串 / Find Special Substring of Length K
# 核心思路：按连续相同字符切分成若干段，只要存在一段的长度恰好等于 k，就说明存在长度为 k 的特殊子字符串。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 题解类
    def hasSpecialSubstring(self, s: str, k: int) -> bool:  # 判断 s 中是否存在长度为 k 的特殊子字符串
        l, n = 0, len(s)  # l 为每一段连续相同字符的起点，n 为字符串长度
        while l < n:  # 依次处理每一段
            r = l  # r 从段起点开始扩展
            while r < n and s[r] == s[l]:  # 向右扩展，直到字符改变或越界
                r += 1  # 继续右移
            if r - l == k:  # 该段长度恰好为 k，即为所求
                return True  # 直接返回存在
            l = r  # 跳到下一段的起点
        return False  # 所有段都不满足，返回不存在
