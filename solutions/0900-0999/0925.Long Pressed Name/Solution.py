# 题目：925. 长按键入（Long Pressed Name）
# 思路：双指针按字符段比对，同一段字符必须相同，且 name 中的段长不能超过 typed 中的段长；最后要求两串同时扫完。
# 时间复杂度：O(m+n)，两个指针各自只前进一次；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isLongPressedName(self, name: str, typed: str) -> bool:  # name：原本要输入的名字；typed：实际键入的字符序列
        m, n = len(name), len(typed)  # m、n 分别是两个串的长度
        i = j = 0  # 双指针：i 扫描 name，j 扫描 typed
        while i < m and j < n:  # 两个串都没扫完时继续比对
            if name[i] != typed[j]:  # 同一段的首字符必须一致，否则不可能是长按造成的差异
                return False  # 不匹配，直接返回 False
            x = i + 1  # 从 i 往后找 name 中这段相同字符的结束位置
            while x < m and name[x] == name[i]:  # 统计 name 中该字符的连续长度
                x += 1  # 继续往后找
            y = j + 1  # 从 j 往后找 typed 中这段相同字符的结束位置
            while y < n and typed[y] == typed[j]:  # 统计 typed 中该字符的连续长度
                y += 1  # 继续往后找
            if x - i > y - j:  # typed 中这一段比 name 中短，说明这个字符少按了
                return False  # 不匹配，直接返回 False
            i, j = x, y  # 两指针同时跳到下一段的起点
        return i == m and j == n  # 两串必须同时扫完，否则有一方还剩字符（多按或漏按）
