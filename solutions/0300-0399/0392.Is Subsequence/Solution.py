# 题目：392. 判断子序列（Is Subsequence）
# 思路：双指针，i 扫 s、j 扫 t，字符相同时 i 前进，j 始终前进，最后看 i 是否走完 s。
# 时间复杂度：O(m + n)，两个串各扫一遍；空间复杂度：O(1)，只用了两个指针。
class Solution:  # LeetCode 约定的题解类
    def isSubsequence(self, s: str, t: str) -> bool:  # s 是待判断的子序列，t 是原字符串
        i = j = 0  # 两个指针同时置 0：i 扫 s，j 扫 t
        while i < len(s) and j < len(t):  # 任一串走完就退出循环
            if s[i] == t[j]:  # 字符相同，说明匹配上了一个字符
                i += 1  # s 的指针后移，等待匹配下一个字符
            j += 1  # 无论是否匹配，t 的指针都要后移
        return i == len(s)  # i 到末尾说明 s 是 t 的子序列
