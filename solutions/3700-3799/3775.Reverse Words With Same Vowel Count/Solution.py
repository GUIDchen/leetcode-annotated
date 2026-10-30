# 3775. 反转元音数相同的单词 / Reverse Words With Same Vowel Count
# 核心思路：先统计第一个单词的元音个数作为基准，之后逐个检查单词，元音数与基准相同的反转后写入答案，再拼回句子。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为字符串长度。
class Solution:  # 定义题解类
    def reverseWords(self, s: str) -> str:  # 返回把元音数相同的单词反转后的新句子
        def calc(w: str) -> int:  # 统计单词中的元音字母个数
            return sum(c in "aeiou" for c in w)  # 逐字符判断是否为元音并求和

        words = s.split()  # 按空白切分出全部单词
        cnt = calc(words[0])  # 第一个单词的元音个数作为基准
        ans = [words[0]]  # 答案列表先放入第一个单词
        for w in words[1:]:  # 依次处理后面的每个单词
            if calc(w) == cnt:  # 元音数与第一个单词相同
                ans.append(w[::-1])  # 反转该单词后加入答案
            else:  # 元音数与基准不同
                ans.append(w)  # 保持原样加入答案
        return " ".join(ans)  # 用空格拼回句子并返回
