# 题目：318. 最大单词长度乘积（Maximum Product of Word Lengths）
# 思路：为每个单词算一个 26 位掩码，两个掩码按位与为 0 表示没有公共字母，此时用长度乘积更新答案。
# 时间复杂度：O(L + n^2)，L 为所有单词的字符总数；空间复杂度：O(n)，只需保存每个单词的掩码。
class Solution:  # LeetCode 约定的题解类
    def maxProduct(self, words: List[str]) -> int:  # words 是单词列表，返回合法单词对的最大长度乘积
        mask = [0] * len(words)  # 预分配掩码列表，mask[i] 保存第 i 个单词的字母集合
        ans = 0  # 记录最大长度乘积，0 表示目前还没有合法单词对
        for i, s in enumerate(words):  # 同时取出下标 i 和单词 s
            for c in s:  # 遍历单词 s 的每个字符
                mask[i] |= 1 << (ord(c) - ord("a"))  # 把字符 c 对应的那一位设为 1，得到该单词的字母集合
            for j, t in enumerate(words[:i]):  # 只与 i 之前的单词配对，避免同一对重复计算
                if (mask[i] & mask[j]) == 0:  # 按位与为 0：两个单词没有任何公共字母
                    ans = max(ans, len(s) * len(t))  # 无公共字母时用两边长度的乘积更新答案
        return ans  # 返回最大乘积，没有合法单词对时为 0
