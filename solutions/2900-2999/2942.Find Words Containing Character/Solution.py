# 题目：2942. 查找包含给定字符的单词（Find Words Containing Character）
# 思路：逐个扫描每个单词，用 in 判断是否含有字符 x，含有就把下标加入结果。
# 时间复杂度：O(L)，L 为所有单词的字符总数；空间复杂度：O(1)，除返回值外不用额外空间。
class Solution:  # LeetCode 约定的题解类
    def findWordsContaining(self, words: List[str], x: str) -> List[int]:  # words：单词列表；x：要查找的字符；返回所有包含 x 的单词下标
        return [i for i, w in enumerate(words) if x in w]  # 列表推导：enumerate 同时给出下标 i 与单词 w，x in w 判断是否包含该字符
