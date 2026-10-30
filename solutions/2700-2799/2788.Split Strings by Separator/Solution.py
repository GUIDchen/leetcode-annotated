# 题目：2788. 按分隔符拆分字符串（Split Strings by Separator）
# 思路：对每个单词按分隔符 split，展平成一维列表，并用 if s 丢弃切分产生的空串。
# 时间复杂度：O(总字符数)，每个字符只被扫描一次；空间复杂度：O(总字符数)，用于存放答案。
class Solution:  # LeetCode 约定的题解类
    def splitWordsBySeparator(self, words: List[str], separator: str) -> List[str]:  # words：待拆分的字符串列表；separator：分隔符字符串
        return [s for w in words for s in w.split(separator) if s]  # 列表推导式：先遍历单词，再逐个 split，最后用 if s 过滤掉空串
