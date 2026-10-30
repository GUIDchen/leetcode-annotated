# 题目：336. 回文对（Palindrome Pairs）
# 核心思路：把单词与下标建成哈希表，对每个单词枚举切分点，用「反转后的另一半」去哈希表里配对，并检查剩余部分本身是否回文。
# 时间复杂度：O(n·L²)，n 为单词数、L 为单词长度，每个切分点都要做切片与反转；空间复杂度：O(n·L)，哈希表保存全部单词。
class Solution:  # LeetCode 约定的题解类
    def palindromePairs(self, words: List[str]) -> List[List[int]]:  # words 是单词列表，返回所有拼接后为回文串的下标对 (i, j)
        d = {w: i for i, w in enumerate(words)}  # 哈希表：单词 → 下标，便于 O(1) 判断某个单词是否存在
        ans = []  # 收集答案下标对
        for i, w in enumerate(words):  # 枚举第一个单词 w 及其下标 i
            for j in range(len(w) + 1):  # 枚举切分点，把 w 拆成前缀 a 和后缀 b（含空前缀、空后缀两种边界）
                a, b = w[:j], w[j:]  # 前缀 a 与后缀 b
                ra, rb = a[::-1], b[::-1]  # 两者的反转，用来在哈希表里查找可以拼在前/后的单词
                if ra in d and d[ra] != i and b == rb:  # 若反转前缀存在且不是自己，且后缀 b 本身是回文，则 ra+a+b 即 ra+w 是回文
                    ans.append([i, d[ra]])  # 记录下标对 (i, 反转前缀所在下标)
                if j and rb in d and d[rb] != i and a == ra:  # 另一侧：反转后缀存在、不是自己，且前缀 a 本身是回文，则 w+rb 是回文；j>0 避免切出空后缀重复计数
                    ans.append([d[rb], i])  # 记录下标对 (反转后缀所在下标, i)
        return ans  # 返回全部满足条件的下标对
