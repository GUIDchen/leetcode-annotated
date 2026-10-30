# 题目：1839. 所有元音按顺序排布的最长子字符串（Longest Substring Of All Vowels in Order）
# 思路：先做行程编码把 word 压成 (字符, 连续长度) 序列，再检查相邻 5 段是否恰为 a,e,i,o,u，是则累加 5 段长度更新答案。
# 时间复杂度：O(n)，行程编码与五段检查均线性；空间复杂度：O(n)，存放行程序列。
class Solution:  # LeetCode 约定的题解类
    def longestBeautifulSubstring(self, word: str) -> int:  # word 是只含小写字母的字符串，返回满足 a→e→i→o→u 递增的最长美丽子串长度
        arr = []  # 行程编码列表，每项是 (字符, 该字符连续出现的次数)
        n = len(word)  # 字符串长度
        i = 0  # i 指向当前这一段的起点
        while i < n:  # 逐段处理，直到字符串末尾
            j = i  # j 用来寻找当前段的结束位置
            while j < n and word[j] == word[i]:  # 跳过所有与 word[i] 相同的字符
                j += 1  # j 后移，继续比较下一个字符
            arr.append((word[i], j - i))  # 记录一段：字符 word[i] 连续出现了 j - i 次
            i = j  # 从下一段起点继续
        ans = 0  # 记录最长美丽子串的长度
        for i in range(len(arr) - 4):  # 枚举起始段；len(arr) - 4 保证后面还剩 4 段
            a, b, c, d, e = arr[i : i + 5]  # 取出连续 5 段，每段是 (字符, 长度) 元组
            if a[0] + b[0] + c[0] + d[0] + e[0] == "aeiou":  # 五段字符拼接后正好是 aeiou，说明这 5 段构成美丽子串
                ans = max(ans, a[1] + b[1] + c[1] + d[1] + e[1])  # 美丽子串取满 5 段最长，用各段长度之和更新答案
        return ans  # 返回最长长度
