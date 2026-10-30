# 题目：1933. 判断字符串是否可分解为值均等的子串（Check if String Is Decomposable Into Value-Equal Substrings）
# 思路：按连续相同字符分段，每段长度 mod 3 只能为 0 或 2，且余 2 的段必须恰好一段。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isDecomposable(self, s: str) -> bool:  # 判断 s 能否拆成若干「长度 3 或长度 2」的同值段，并且长度 2 的段恰好一个
        i, n = 0, len(s)  # i 是当前连续段的左端点，n 是字符串长度
        cnt2 = 0  # 记录「长度 mod 3 余 2」的段数，这些段各要用一个长度 2 的块
        while i < n:  # 逐段处理，直到走完整个字符串
            j = i  # j 用来扫描当前连续相同字符段的右边界
            while j < n and s[j] == s[i]:  # 只要字符相同就继续向右扩展
                j += 1  # 右移一格
            if (j - i) % 3 == 1:  # 余 1 的长度无法用 3 与 2 拼出，直接判失败
                return False  # 返回不可分解
            cnt2 += (j - i) % 3 == 2  # 布尔值参与加法：余数为 2 时计数器加 1
            if cnt2 > 1:  # 长度 2 的段已经超过一个
                return False  # 不满足「恰好一个」的要求
            i = j  # 跳到下一段的起点
        return cnt2 == 1  # 必须恰好存在一个长度 2 的段
