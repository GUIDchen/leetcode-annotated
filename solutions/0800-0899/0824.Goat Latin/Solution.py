# 题目：824. 山羊拉丁文（Goat Latin）
# 思路：按空格切分句子，逐词判断首字母是否为元音：不是元音就把首字母挪到末尾；随后统一追加 ma，再按单词序号追加相应个数的 a，最后用空格拼回。
# 时间复杂度：O(L)，L 为句子总长度；空间复杂度：O(L)，用于存放结果。
class Solution:  # LeetCode 约定的题解类
    def toGoatLatin(self, sentence: str) -> str:  # sentence：按空格分隔的英文句子
        ans = []  # 存放转换后的每个单词
        for i, word in enumerate(sentence.split()):  # 切分单词，i 从 0 开始，决定追加几个 a
            if word.lower()[0] not in ['a', 'e', 'i', 'o', 'u']:  # 首字母不是元音（先转小写以兼容大写字母）
                word = word[1:] + word[0]  # 把首字母移到单词末尾
            word += 'ma'  # 所有单词统一追加 ma
            word += 'a' * (i + 1)  # 第 i+1 个单词追加 i+1 个 a
            ans.append(word)  # 收集转换结果
        return ' '.join(ans)  # 用空格拼成最终句子
