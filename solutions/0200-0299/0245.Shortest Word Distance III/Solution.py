# 题目：245. 最短单词距离 III（Shortest Word Distance III）
# 思路：分两种情况。两词相同时只保留上一次出现的下标，距离取相邻两次出现之差；不同时退化为记录两个最近下标再取差值。
# 时间复杂度：O(n)，一遍扫描；空间复杂度：O(1)，只用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def shortestWordDistance(self, wordsDict: List[str], word1: str, word2: str) -> int:  # wordsDict 是单词列表，返回 word1 与 word2 的最短距离
        ans = len(wordsDict)  # 最小距离，先取一个必然不小于答案的上界
        if word1 == word2:  # 两个单词相同时，要找两个不同位置上的同一个单词
            j = -1  # 上一次出现的下标，-1 表示还没出现
            for i, w in enumerate(wordsDict):  # 从左到右扫描，同时拿到下标 i 与单词 w
                if w == word1:  # 遇到目标单词
                    if j != -1:  # 前面出现过一次，才能与当前位置配对
                        ans = min(ans, i - j)  # 相邻两次出现的下标差就是候选距离
                    j = i  # 把当前下标记为最近一次出现位置
        else:  # 两个单词不同，退化为普通的最短单词距离
            i = j = -1  # 两个单词最近一次出现的下标，-1 表示还没出现
            for k, w in enumerate(wordsDict):  # 从左到右扫描，同时拿到下标 k 与单词 w
                if w == word1:  # 遇到 word1
                    i = k  # 记录 word1 的下标
                if w == word2:  # 遇到 word2
                    j = k  # 记录 word2 的下标
                if i != -1 and j != -1:  # 两者都出现过才能计算距离
                    ans = min(ans, abs(i - j))  # 用下标差更新最小距离
        return ans  # 返回最小距离
