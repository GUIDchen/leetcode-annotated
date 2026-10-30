# 题目：1592. 重新排列单词间的空格（Rearrange Spaces Between Words）
# 思路：统计空格总数与单词个数，把空格尽量均匀地放进单词间隙，除不尽的余数补在末尾。
# 时间复杂度：O(n)，统计、切分与拼接都是线性；空间复杂度：O(n)，保存切分出的单词。
class Solution:  # LeetCode 约定的题解类
    def reorderSpaces(self, text: str) -> str:  # text 为原始字符串
        spaces = text.count(" ")  # 空格的总个数
        words = text.split()  # 按任意空白切分出所有单词，自动去掉多余空格
        if len(words) == 1:  # 只有一个单词时没有“间隙”可分
            return words[0] + " " * spaces  # 所有空格全部堆到单词末尾
        cnt, mod = divmod(spaces, len(words) - 1)  # 均分到 len(words)-1 个间隙，余数记入 mod
        return (" " * cnt).join(words) + " " * mod  # 用 cnt 个空格连接单词，末尾再补上剩余空格
