# 题目：422. 有效的单词方块（Valid Word Square，会员题）
# 思路：单词方块要求第 i 行第 j 列等于第 j 行第 i 列；逐字符检查对称位置是否相等，同时防止行列长度不齐导致越界。
# 时间复杂度：O(L)，L 是所有单词的字符总数；空间复杂度：O(1)，只用了下标变量。
class Solution:  # LeetCode 约定的题解类
    def validWordSquare(self, words: List[str]) -> bool:  # words 是单词列表，判断这些单词是否构成有效的单词方块
        m = len(words)  # m 是行数，同时也是转置后应有的行数
        for i, w in enumerate(words):  # 同时取得行下标 i 与当前单词 w
            for j, c in enumerate(w):  # 同时取得字符下标 j 与当前字符 c
                if j >= m or i >= len(words[j]) or c != words[j][i]:  # 下标越界或对称位置字符不相等，说明不是单词方块
                    return False  # 立即判假
        return True  # 所有位置都对称相等，返回真
