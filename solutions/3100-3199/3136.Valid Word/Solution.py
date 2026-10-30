# 题目：3136. 有效单词（Valid Word）
# 思路：先建好元音集合，再扫一遍单词：非字母数字直接判非法，字母区分元音/辅音，最后要求两者都出现过。
# 时间复杂度：O(n)，n 为单词长度；空间复杂度：O(1)，元音集合大小固定为 10。
class Solution:  # LeetCode 约定的题解类
    def isValid(self, word: str) -> bool:  # word 是待校验的单词，返回它是否有效
        if len(word) < 3:  # 题目要求单词长度至少为 3
            return False  # 长度不足直接判非法
        has_vowel = has_consonant = False  # 分别记录是否已出现元音、是否已出现辅音
        vs = set("aeiouAEIOU")  # 大小写共 10 个元音字母放进集合，便于 O(1) 查询
        for c in word:  # 遍历单词的每个字符
            if not c.isalnum():  # 出现既不是字母也不是数字的字符
                return False  # 直接判定该单词无效
            if c.isalpha():  # 只有字母才需要区分元音与辅音
                if c in vs:  # 命中元音集合
                    has_vowel = True  # 标记已出现元音
                else:  # 不在元音集合中的字母
                    has_consonant = True  # 那就是辅音，标记已出现辅音
        return has_vowel and has_consonant  # 元音与辅音都出现过才算有效单词
