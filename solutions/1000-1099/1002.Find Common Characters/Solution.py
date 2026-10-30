# 题目：1002. 查找共用字符（Find Common Characters）
# 思路：以第一个单词的字符计数为基准，逐个与其它单词的计数取最小值，得到每个字符在答案中应出现的次数。
# 时间复杂度：O(L + 26n)，L 为所有单词总长度；空间复杂度：O(26)。
class Solution:  # LeetCode 约定的题解类
    def commonChars(self, words: List[str]) -> List[str]:  # words：单词数组；返回在所有单词中都出现的字符（按最少出现次数计）
        cnt = Counter(words[0])  # 先用第一个单词的字符计数作为基准
        for w in words:  # 依次与每个单词求「字符计数交集」
            t = Counter(w)  # 当前单词的字符计数
            for c in cnt:  # 遍历基准里已有的字符（只改值不改键，可以边遍历边改）
                cnt[c] = min(cnt[c], t[c])  # 取各单词中该字符出现次数的最小值，缺失的字符 Counter 会返回 0
        return list(cnt.elements())  # elements() 按次数把字符逐个展开，再转成字符串列表返回
