# 题目：3304. 找出第 K 个字符 I（Find the K-th Character in String Game I）
# 思路：按生成规则不断把「每个字符的下一字母」追加到串尾，直到长度 >= k，直接取第 k 个字符。
# 时间复杂度：O(k)，串长倍增到 >= k，总操作数受 2k 约束；空间复杂度：O(k)，保存生成的整串。
class Solution:  # LeetCode 约定的题解类
    def kthCharacter(self, k: int) -> str:  # k：要查询的位置（从 1 开始）；返回生成串的第 k 个字符
        word = [0]  # word 用 0..25 存字符相对 'a' 的偏移
        while len(word) < k:  # 长度不足 k 时继续扩展
            word.extend([(x + 1) % 26 for x in word])  # 把现有每个字符的下一个字母（'z' 之后回绕到 'a'）一次性追加到串尾
        return chr(ord("a") + word[k - 1])  # 偏移加 'a' 转回字符并返回（下标从 0 开始，所以是 k-1）
