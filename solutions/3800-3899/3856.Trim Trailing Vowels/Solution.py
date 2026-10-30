# 3856. 移除尾部元音字母 / Trim Trailing Vowels（简单）
# 核心思路：从字符串末尾向前扫描，跳过所有连续的元音字符，保留下来的前缀就是答案。
# 复杂度：时间 O(n)，空间 O(n)（返回的子串需要 O(n) 拷贝）。
class Solution:  # 设计一个算法：删掉字符串末尾连续的元音字母
    def trimTrailingVowels(self, s: str) -> str:  # 返回去掉全部尾部元音后的字符串
        i = len(s) - 1  # 下标指向字符串末尾，准备从后往前扫描
        while i >= 0 and s[i] in "aeiou":  # 只要当前字符仍是元音 aeiou，就继续左移
            i -= 1  # 跳过这个尾部元音
        return s[: i + 1]  # 保留前 i + 1 个字符，即凑出不含尾部元音的前缀
