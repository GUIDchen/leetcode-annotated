# 题目：1078. Bigram 分词（Occurrences After Bigram）
# 思路：用 split() 把 text 按空白切成单词列表，再顺序检查每个位置 i，若连续两个词分别是 first、second，就把第三个词收集起来。
# 时间复杂度：O(n)，n 为文本长度，切分与扫描各一遍；空间复杂度：O(n)，用于保存单词列表与结果。
class Solution:  # LeetCode 约定的题解类
    def findOcurrences(self, text: str, first: str, second: str) -> List[str]:  # text 是原文，first、second 是二元组的前两个词
        words = text.split()  # 按任意空白切分文本，得到单词列表
        ans = []  # 存放所有符合条件的第三个单词
        for i in range(len(words) - 2):  # i 最多取到 len-3，保证 i+2 不越界
            a, b, c = words[i : i + 3]  # 一次取出连续的三个单词并分别解包
            if a == first and b == second:  # 前两个词正好是 first、second
                ans.append(c)  # 把紧随其后的第三个词加入答案
        return ans  # 返回按原顺序收集的结果
