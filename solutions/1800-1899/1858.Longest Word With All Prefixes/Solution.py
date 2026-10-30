# 题目：1858. 包含所有前缀的最长单词（Longest Word With All Prefixes）
# 思路：把所有单词插入字典树，再逐个单词沿树下落，检查途经的每个结点都是某个单词的结尾；在满足条件的单词中取最长、长度相同取字典序最小。
# 时间复杂度：O(L)，L 为所有单词的字符总数；空间复杂度：O(L)，字典树结点数。
class Trie:  # 字典树结点：用 26 个孩子表示小写字母
    __slots__ = ["children", "is_end"]  # 用 __slots__ 限定属性，减少每个结点的内存开销

    def __init__(self):  # 构造：初始化孩子数组与结尾标记
        self.children: List[Trie | None] = [None] * 26  # children[idx]：字母 idx 的子结点，None 表示该前缀不存在
        self.is_end: bool = False  # is_end：是否有单词以当前结点结尾

    def insert(self, w: str) -> None:  # 插入单词 w
        node = self  # 从根结点开始
        for c in w:  # 逐字符插入
            idx = ord(c) - ord("a")  # 字符映射到 0..25
            if not node.children[idx]:  # 该前缀对应的子结点还不存在
                node.children[idx] = Trie()  # 新建结点挂上去
            node = node.children[idx]  # 移动到子结点继续插
        node.is_end = True  # 标记单词结尾

    def search(self, w: str) -> bool:  # 检查 w 的每个前缀是否都是完整单词
        node = self  # 从根结点开始
        for c in w:  # 逐字符向下走
            idx = ord(c) - ord("a")  # 字符映射到 0..25
            node = node.children[idx]  # 下降到子结点（插入时已保证存在）
            if not node.is_end:  # 某个前缀不是完整单词
                return False  # 立即返回 False
        return True  # 全部前缀都是单词，返回 True


class Solution:  # LeetCode 约定的题解类
    def longestWord(self, words: List[str]) -> str:  # words：候选单词，返回满足条件的最长单词
        trie = Trie()  # 建立字典树
        for w in words:  # 先把所有单词插入树中
            trie.insert(w)  # 逐个插入
        ans = ""  # 答案初值：空串
        for w in words:  # 遍历所有单词挑最优答案
            if (len(w) > len(ans) or len(w) == len(ans) and w < ans) and trie.search(w):  # 长度更长，或长度相同而字典序更小，并且所有前缀都在集合中
                ans = w  # 更新答案
        return ans  # 返回答案，没有合法单词时就是空串
