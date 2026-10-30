# 题目：208. 实现 Trie（Implement Trie (Prefix Tree)）
# 思路：每个节点开 26 个儿子指向下一层，外加 is_end 标记；插入缺路径则新建，查询先走到底再看标记。
# 时间复杂度：insert/search/startsWith 均为 O(L)，L 为字符串长度；空间复杂度：O(总字符数)，新字符最坏各建一个节点。
class Trie:  # 前缀树节点（同时作为树根）：26 个儿子 + 单词结尾标记
    def __init__(self):  # 构造一个空节点
        self.children = [None] * 26  # 26 个槽位对应 a~z，None 表示该字母分支不存在
        self.is_end = False  # 默认本节点不是任何单词的结尾

    def insert(self, word: str) -> None:  # 插入单词
        node = self  # 从根节点开始向下建路径
        for c in word:  # 逐个字符处理
            idx = ord(c) - ord('a')  # 把字符映射成 0~25 的下标
            if node.children[idx] is None:  # 该字母分支还不存在
                node.children[idx] = Trie()  # 新建子节点接上
            node = node.children[idx]  # 走到该子节点
        node.is_end = True  # 末尾节点打上是完整单词的标记

    def search(self, word: str) -> bool:  # 查询完整单词是否存在
        node = self._search_prefix(word)  # 先沿 word 走到对应节点
        return node is not None and node.is_end  # 路径存在且是单词结尾才算找到

    def startsWith(self, prefix: str) -> bool:  # 查询是否存在以此前缀开头的单词
        node = self._search_prefix(prefix)  # 沿前缀向下走
        return node is not None  # 路径存在即说明有单词以它为前缀

    def _search_prefix(self, prefix: str):  # 内部工具：返回走完前缀后停下的节点，走不通返回 None
        node = self  # 从根开始
        for c in prefix:  # 逐个字符向下匹配
            idx = ord(c) - ord('a')  # 字符映射成下标
            if node.children[idx] is None:  # 分支缺失
                return None  # 说明不存在该前缀，直接返回 None
            node = node.children[idx]  # 沿分支向下
        return node  # 返回匹配完前缀后所在的节点


# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)
