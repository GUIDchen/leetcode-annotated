# 3838. 带权单词映射 / Weighted Word Mapping（简单）
# 核心思路：把每个单词的字母替换成给定权重后求和，对 26 取模得到 0..25 的偏移量，再用 25 减去它换成字母，逐词拼接成结果串。
# 复杂度：时间 O(所有单词字符总数)，空间 O(单词个数)。
class Solution:  # LeetCode 要求的类名
    def mapWordWeights(self, words: List[str], weights: List[int]) -> str:  # 返回每个单词映射得到的字符拼接成的字符串
        ans = []  # 保存各个单词的映射字符
        for w in words:  # 逐个单词处理
            s = sum(weights[ord(c) - ord('a')] for c in w)  # 累加单词中每个字母对应的权重
            ans.append(ascii_lowercase[25 - s % 26])  # 对 26 取模后用 25 减去它取字母（权重和越大，字母越靠前）
        return ''.join(ans)  # 拼接成最终字符串
