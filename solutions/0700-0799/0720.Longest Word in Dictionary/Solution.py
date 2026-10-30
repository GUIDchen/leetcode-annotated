# 题目：720. 词典中最长的单词（Longest Word in Dictionary）
# 思路：用字典树存下所有单词；一个单词合法 <=> 它的每个前缀（含自身）都是某个单词的结尾；再按长度优先、字典序次之挑最优。
# 时间复杂度：O(sum|w|)；空间复杂度：O(sum|w| * 26)（字典树节点）。
class Trie:  # 字典树节点类
    def __init__(self):  # 初始化节点
        self.children: List[Optional[Trie]] = [None] * 26  # 26 个字母子指针，初始全为空
        self.is_end = False  # 是否是某个单词的结尾

    def insert(self, w: str):  # 把单词 w 插入字典树
        node = self  # 从根节点开始
        for c in w:  # 逐字符向下扩展
            idx = ord(c) - ord("a")  # 字母映射为 0~25
            if node.children[idx] is None:  # 分支还不存在
                node.children[idx] = Trie()  # 新建子节点
            node = node.children[idx]  # 下移一层
        node.is_end = True  # 词尾打标记，表示 w 是完整单词

    def search(self, w: str) -> bool:  # 判断 w 的每个前缀（含自身）是否都是单词
        node = self  # 从根开始
        for c in w:  # 逐字符下降
            idx = ord(c) - ord("a")  # 字母转下标
            if node.children[idx] is None:  # 路径不存在
                return False  # 该前缀不可能构成单词，直接失败
            node = node.children[idx]  # 下移一层
            if not node.is_end:  # 中途某个前缀不是完整单词
                return False  # 立即判定不合法
        return True  # 所有前缀都合法


class Solution:  # LeetCode 约定的题解类
    def longestWord(self, words: List[str]) -> str:  # words：候选单词列表
        trie = Trie()  # 建立字典树
        for w in words:  # 遍历所有单词
            trie.insert(w)  # 插入树中
        ans = ""  # 记录当前最优答案
        for w in words:  # 逐个候选单词检查
            if trie.search(w) and (  # 单词合法，并且满足下面关于长度与字典序的条件
                len(ans) < len(w) or (len(ans) == len(w) and ans > w)  # 比当前答案更长，或等长时字典序更小
            ):  # 条件表达式结束
                ans = w  # 更新答案
        return ans  # 返回最长的合法单词
