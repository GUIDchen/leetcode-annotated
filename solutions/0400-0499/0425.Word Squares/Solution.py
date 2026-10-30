# 题目：425. 单词方块（Word Squares）
# 思路：把每个单词连同下标插入前缀树，节点记录经过该前缀的单词下标；回溯逐行填词，用已选各行的第 idx 个字符拼成前缀，在前缀树里查下一行可选单词。
# 时间复杂度：建树 O(nL)，回溯开销与合法方案数成正比（n 为单词数、L 为单词长度）；空间复杂度：O(nL)，即前缀树节点数。
class Trie:  # 前缀树：按前缀快速找出可以放在下一行的候选单词
    def __init__(self):  # 初始化一个前缀树节点
        self.children = [None] * 26  # 26 个小写字母对应的子节点，没有分支时为 None
        self.v = []  # 经过该前缀的所有单词下标

    def insert(self, w, i):  # 把单词 w 及其下标 i 插入前缀树
        node = self  # 从根节点开始往下走
        for c in w:  # 逐字符向下
            idx = ord(c) - ord('a')  # 把字符映射成 0 到 25 的下标
            if node.children[idx] is None:  # 该字符对应的分支还不存在
                node.children[idx] = Trie()  # 新建一个节点接上去
            node = node.children[idx]  # 走到子节点
            node.v.append(i)  # 当前前缀能被下标 i 的单词匹配，记录下来

    def search(self, w):  # 查询以 w 为前缀的所有单词下标
        node = self  # 从根节点开始往下走
        for c in w:  # 沿前缀逐字符下行
            idx = ord(c) - ord('a')  # 把字符映射成 0 到 25 的下标
            if node.children[idx] is None:  # 前缀不存在，说明没有单词能匹配
                return []  # 返回空列表
            node = node.children[idx]  # 继续下行
        return node.v  # 返回所有以 w 为前缀的单词下标


class Solution:  # LeetCode 题解类
    def wordSquares(self, words: List[str]) -> List[List[str]]:  # words：长度相同的单词表；返回所有合法的单词方块
        def dfs(t):  # t 是当前已经选好的若干行
            if len(t) == len(words[0]):  # 行数等于单词长度，说明方块已经填满
                ans.append(t[:])  # 复制一份当前方案存入答案（t 之后还会被修改，必须拷贝）
                return  # 本分支搜索结束
            idx = len(t)  # 行数就是下一行需要匹配的前缀长度
            pref = [v[idx] for v in t]  # 取已选每一行第 idx 个字符，组成竖向的列前缀
            indexes = trie.search(''.join(pref))  # 查前缀树，得到可以作为下一行的单词下标
            for i in indexes:  # 依次尝试每个候选单词
                t.append(words[i])  # 选中该单词作为下一行
                dfs(t)  # 递归填后面的行
                t.pop()  # 回溯：撤销选择，继续尝试下一个候选

        trie = Trie()  # 建一棵空前缀树
        ans = []  # 存放所有合法的单词方块
        for i, w in enumerate(words):  # 遍历每个单词及其下标
            trie.insert(w, i)  # 把单词按下标插入前缀树
        for w in words:  # 每个单词都可以作为方块的第一行
            dfs([w])  # 以该单词为起点开始回溯搜索
        return ans  # 返回全部答案
