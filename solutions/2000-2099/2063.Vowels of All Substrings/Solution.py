# 题目：2063. 所有子字符串中的元音（Vowels of All Substrings）
# 思路：按每个元音字符的贡献计数：下标 i 处的元音会被 (i+1)*(n-i) 个子串包含，逐位累加即可。
# 时间复杂度：O(n)，只扫一遍字符串；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countVowels(self, word: str) -> int:  # word：输入字符串；返回所有子串中的元音总数
        n = len(word)  # 字符串长度
        return sum((i + 1) * (n - i) for i, c in enumerate(word) if c in 'aeiou')  # 枚举每个元音字符，累加包含它的子串数
