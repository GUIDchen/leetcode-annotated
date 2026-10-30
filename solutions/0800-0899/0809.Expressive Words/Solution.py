# 题目：809. 情感丰富的文字（Expressive Words）
# 思路：把 s 和每个单词切成「连续相同字符段」，逐段比较字符与段长，满足扩张规则才计数。
# 时间复杂度：O(L * |s|)，L 为 words 长度；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def expressiveWords(self, s: str, words: List[str]) -> int:  # s 是目标串，words 是待检查的单词列表
        def check(s, t):  # 内层辅助函数：判断 t 能否扩张成 s
            m, n = len(s), len(t)  # m、n 分别是 s 与 t 的长度
            if n > m:  # t 更长时无法收缩，直接判否
                return False  # 返回 False
            i = j = 0  # 双指针：i 指向 s，j 指向 t
            while i < m and j < n:  # 两串都没扫完时逐段比较
                if s[i] != t[j]:  # 段首字符必须一致
                    return False  # 返回 False
                k = i  # k 用于统计 s 中与 s[i] 相同的连续字符个数
                while k < m and s[k] == s[i]:  # 向后扫描相同字符
                    k += 1  # 移动扫描指针
                c1 = k - i  # c1 是 s 中这段字符的个数
                i, k = k, j  # i 进入 s 的下一段；k 重置为 j，开始统计 t 的段长
                while k < n and t[k] == t[j]:  # 向后扫描 t 中相同的字符
                    k += 1  # 移动扫描指针
                c2 = k - j  # c2 是 t 中这段字符的个数
                j = k  # j 进入 t 的下一段
                if c1 < c2 or (c1 < 3 and c1 != c2):  # 段长不能被缩小；且 s 这段不足 3 个时长度必须相等
                    return False  # 返回 False
            return i == m and j == n  # 两串必须同时扫完才是合法扩张

        return sum(check(s, t) for t in words)  # 对每个单词调用 check，True 计作 1，求和即答案
