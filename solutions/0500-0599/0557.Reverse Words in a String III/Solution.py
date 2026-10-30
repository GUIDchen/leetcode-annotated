# 题目：557. 反转字符串中的单词 III（Reverse Words in a String III）
# 核心思路：按空白切分出单词，每个单词用切片 [::-1] 反转，再用单个空格连接回去。
# 时间复杂度：O(n)，每个字符处理常数次；空间复杂度：O(n)，用于存放结果字符串。
class Solution:  # LeetCode 约定的题解类
    def reverseWords(self, s: str) -> str:  # s 为以单个空格分隔的句子，返回每个单词内部反转后的句子
        return " ".join(t[::-1] for t in s.split())  # split() 按任意空白切词，t[::-1] 反转单词，最后用一个空格重新连接
