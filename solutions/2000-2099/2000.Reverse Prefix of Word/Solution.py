# 题目：2000. 反转单词前缀（Reverse Prefix of Word）
# 思路：先找到字符 ch 第一次出现的下标 i，若存在则把前缀 [0, i] 反转后与后缀拼接，不存在则原样返回。
# 时间复杂度：O(n)，查找与切片拼接各 O(n)；空间复杂度：O(n)，切片与拼接产生新字符串。
class Solution:  # LeetCode 约定的题解类
    def reversePrefix(self, word: str, ch: str) -> str:  # word：输入单词；ch：需要第一次出现的字符
        i = word.find(ch)  # 查找 ch 第一次出现的下标，找不到时返回 -1
        return word if i == -1 else word[i::-1] + word[i + 1 :]  # 未找到返回原串；否则前缀 i..0 逆序再接上 i+1 之后的后缀
