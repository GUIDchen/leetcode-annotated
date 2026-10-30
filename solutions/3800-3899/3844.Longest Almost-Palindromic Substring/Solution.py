# 3844. 最长的准回文子字符串 / Longest Almost-Palindromic Substring（中等）
# 核心思路：枚举每个回文中心向外扩展，再分别尝试跳过左端或右端的一个字符继续扩展，取更长的长度。
# 复杂度：时间 O(n^2)，空间 O(1)。
class Solution:  # 题解类（LeetCode 约定类名）
    def almostPalindromic(self, s: str) -> int:  # 返回字符串 s 中最长准回文子串的长度
        def f(l: int, r: int) -> int:  # 闭包 f：以 (l, r) 为中心扩展，返回该中心可得到的最长准回文长度
            while l >= 0 and r < n and s[l] == s[r]:  # 第一阶段：常规回文扩展，两端字符相同就继续向外
                l -= 1  # 左指针左移
                r += 1  # 右指针右移
            l1, r1 = l - 1, r  # 方案一：跳过左边界外的那个字符，从 l-1 与 r 继续匹配
            l2, r2 = l, r + 1  # 方案二：跳过右边界外的那个字符，从 l 与 r+1 继续匹配
            while l1 >= 0 and r1 < n and s[l1] == s[r1]:  # 用方案一继续向外扩展
                l1 -= 1  # 左指针左移
                r1 += 1  # 右指针右移
            while l2 >= 0 and r2 < n and s[l2] == s[r2]:  # 用方案二继续向外扩展
                l2 -= 1  # 左指针左移
                r2 += 1  # 右指针右移
            return min(n, max(r1 - l1 - 1, r2 - l2 - 1))  # 两方案长度取较大值，再与 n 取小防止越界

        n = len(s)  # n 为字符串长度，供闭包与循环复用
        ans = 0  # ans 记录最终答案（最长准回文子串长度）
        for i in range(n):  # 枚举每一个扩展中心
            a = f(i, i)  # 奇数长度中心：以 i 为单个字符中心
            b = f(i, i + 1)  # 偶数长度中心：以 i 与 i+1 之间为中心
            ans = max(ans, a, b)  # 更新答案
        return ans  # 返回最长准回文子串的长度
