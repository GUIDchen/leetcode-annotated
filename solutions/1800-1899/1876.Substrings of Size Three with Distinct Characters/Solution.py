# 题目：1876. 长度为三且各字符不同的子字符串（Substrings of Size Three with Distinct Characters）
# 思路：滑动窗口 + 26 位二进制掩码记录窗口内出现过的字母，窗口内字符始终互不重复；窗口长度 >= 3 时，以 r 结尾的最后 3 个字符即一个合法子串。
# 时间复杂度：O(n)，左右指针各自只前进一次；空间复杂度：O(1)，只用常数个整型变量与一个掩码。
class Solution:  # LeetCode 约定的题解类
    def countGoodSubstrings(self, s: str) -> int:  # s：只含小写字母的字符串；返回长度恰为 3 且三字符互不相同的子串个数
        ans = mask = l = 0  # ans：合法子串个数；mask：窗口内字母集合；l：窗口左指针（三者一起置 0）
        for r, x in enumerate(map(lambda c: ord(c) - 97, s)):  # 逐个取字符并映射成 0..25：r 是右指针下标，x 是当前字符对应的整数
            while mask >> x & 1:  # (mask >> x) & 1 为真表示 x 已在窗口中，出现重复需要收缩左边界
                y = ord(s[l]) - 97  # 取出左端字符的 ASCII 码并减去 97，得到它对应的 0..25 整数 y
                mask ^= 1 << y  # 从窗口集合中清除 y 这一位（异或清零）
                l += 1  # 左指针右移一位，窗口缩小
            mask |= 1 << x  # 把当前字符 x 加入窗口集合
            ans += int(r - l + 1 >= 3)  # 窗口长度 >= 3 时，以 r 结尾的最后 3 个字符互不相同，计数加 1
        return ans  # 返回合法子串总数
