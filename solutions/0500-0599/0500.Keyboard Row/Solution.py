# 题目：500. 键盘行（Keyboard Row）
# 思路：把键盘三行的字母各自做成集合，对每个单词取它去重后的字母集合，只要它是某一行集合的子集，就说明该词能只用一行键盘敲出来。
# 时间复杂度：O(L)，L 是所有单词的字符总数；空间复杂度：O(1)，三个字母集合大小固定。
class Solution:  # LeetCode 约定的题解类
    def findWords(self, words: List[str]) -> List[str]:  # words 是待筛选的单词列表
        s1 = set('qwertyuiop')  # 键盘第一行的字母集合
        s2 = set('asdfghjkl')  # 键盘第二行的字母集合
        s3 = set('zxcvbnm')  # 键盘第三行的字母集合
        ans = []  # 保存可以只用同一行键盘敲出的单词
        for w in words:  # 逐个单词判断
            s = set(w.lower())  # 转小写后去重成字符集合，从而忽略大小写差异
            if s <= s1 or s <= s2 or s <= s3:  # 集合是某一行的子集，说明该词所有字母都落在同一行
                ans.append(w)  # 符合条件就按原样（保留原大小写）加入答案
        return ans  # 返回筛选结果
