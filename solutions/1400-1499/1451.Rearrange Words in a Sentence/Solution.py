# 题目：1451. 重新排列句子中的单词（Rearrange Words in a Sentence）
# 核心思路：切分单词 → 首单词转小写 → 按长度稳定排序（等长保持原相对顺序）→ 首单词首字母大写 → 用空格连接。
# 时间复杂度：O(L + k log k)，L 为句子长度、k 为单词数；空间复杂度：O(L)，存放切分出的单词。
class Solution:  # LeetCode 约定的题解类
    def arrangeWords(self, text: str) -> str:  # 把句子按单词长度重新排列后返回
        words = text.split()  # split() 不带参数，按任意连续空白切分成单词列表
        words[0] = words[0].lower()  # 先把首单词整体转成小写，便于后面统一处理大小写
        words.sort(key=len)  # 按单词长度排序；Python 的 sort 是稳定排序，等长单词保持原顺序
        words[0] = words[0].title()  # 排序后最前面的（最短的）单词，首字母改回大写
        return " ".join(words)  # 用单个空格把所有单词重新连接成句子并返回
