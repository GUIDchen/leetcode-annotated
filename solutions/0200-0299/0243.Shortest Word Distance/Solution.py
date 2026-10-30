# 题目：243. 最短单词距离（Shortest Word Distance）
# 思路：一次扫描记录两个单词各自最近一次出现的下标，每当两者都出现过，就用下标差更新最小距离。
# 时间复杂度：O(n)，只扫一遍单词列表；空间复杂度：O(1)，只用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def shortestDistance(self, wordsDict: List[str], word1: str, word2: str) -> int:  # wordsDict 是单词列表，返回 word1 与 word2 的最短距离
        i = j = -1  # 两个单词最近一次出现的下标，-1 表示还没出现
        ans = inf  # 最小距离，先置为正无穷
        for k, w in enumerate(wordsDict):  # 从左到右扫描，同时拿到下标 k 与单词 w
            if w == word1:  # 遇到 word1，更新它的最近位置
                i = k  # 记录 word1 的当前下标
            if w == word2:  # 遇到 word2，更新它的最近位置
                j = k  # 记录 word2 的当前下标
            if i != -1 and j != -1:  # 两个单词都出现过，才能计算距离
                ans = min(ans, abs(i - j))  # 用当前下标差更新最小距离
        return ans  # 返回最小距离
