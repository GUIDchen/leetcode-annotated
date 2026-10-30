# 题目：151. 反转字符串中的单词（Reverse Words in a String）
# 思路：双指针逐个切出单词并收集，最后把单词列表反转后用单个空格拼接。
# 时间复杂度：O(n)，每个字符只被扫描一次；空间复杂度：O(n)，需要列表保存所有单词。
class Solution:  # 题目要求的题解类
    def reverseWords(self, s: str) -> str:  # s 为输入字符串，返回单词顺序反转后的结果
        words = []  # 存放切分出来的单词
        i, n = 0, len(s)  # i 是扫描下标，n 是字符串长度
        while i < n:  # 逐个单词提取
            while i < n and s[i] == " ":  # 跳过单词之间的连续空格
                i += 1  # 下标前进
            if i < n:  # 跳完空格后还有字符，说明遇到一个单词
                j = i  # j 用来找单词的右边界
                while j < n and s[j] != " ":  # 一直走到单词末尾（遇到空格或串尾）
                    j += 1  # 右边界后移
                words.append(s[i:j])  # 取出这段单词存进列表
                i = j  # 从单词末尾继续扫描
        return " ".join(words[::-1])  # 单词列表反转后用单个空格拼回字符串
