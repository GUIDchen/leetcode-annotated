# 题目：418. 屏幕可显示句子的数量（Sentence Screen Fitting，会员题）
# 思路：把句子拼成「每个单词后缀一个空格」的循环串，用 cur 跨行累计已排下的字符数，每行先加 cols 再按空格边界回退。
# 时间复杂度：O(rows * cols)，每行最坏回退 cols 步；空间复杂度：O(L)，L 是整个句子的字符数。
class Solution:  # LeetCode 约定的题解类
    def wordsTyping(self, sentence: List[str], rows: int, cols: int) -> int:  # sentence 是单词列表，rows/cols 是屏幕行数与每行字符数，返回能完整显示的句子遍数
        s = " ".join(sentence) + " "  # 用空格把句子连成循环串，末尾再加一个空格，方便按空格边界判断
        m = len(s)  # m 是循环串长度，用取模实现无限重复
        cur = 0  # cur 是已排下的字符总数，跨行累计
        for _ in range(rows):  # 逐行填充屏幕
            cur += cols  # 先假设本行能放满 cols 个字符
            if s[cur % m] == " ":  # 该位置是空格，说明正好落在单词边界上
                cur += 1  # 跳过这个空格，下一个单词从下一行开头开始
            while cur and s[(cur - 1) % m] != " ":  # 否则单词被行尾截断，往回退到最近的空格之后
                cur -= 1  # 回退一个字符
        return cur // m  # 一个完整句子占 m 个字符（含句尾空格），整除后就是完整遍数
