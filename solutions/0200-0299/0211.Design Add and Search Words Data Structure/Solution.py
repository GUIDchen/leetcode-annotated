# 题目：211. 添加与搜索单词 - 数据结构设计（Design Add and Search Words Data Structure）
# 思路：前缀树存单词；搜索时遇到普通字符只走唯一分支，遇到通配符 . 就枚举 26 个分支递归回溯。
# 时间复杂度：addWord 为 O(L)；search 最坏 O(26^L)，L 为单词长度；空间复杂度：O(总字符数)。
class Trie:  # 前缀树节点：26 个儿子 + 单词结尾标记
    def __init__(self):  # 构造一个空节点
        self.children = [None] * 26  # 26 个槽位对应 a~z，None 表示分支不存在
        self.is_end = False  # 默认不是任何单词的结尾


class WordDictionary:  # 支持 . 通配的单词字典
    def __init__(self):  # 构造：只建一棵空前缀树
        self.trie = Trie()  # 前缀树根节点

    def addWord(self, word: str) -> None:  # 添加单词
        node = self.trie  # 从根节点出发
        for c in word:  # 逐个字符向下建路径
            idx = ord(c) - ord('a')  # 字符映射成 0~25 的下标
            if node.children[idx] is None:  # 该字母分支还不存在
                node.children[idx] = Trie()  # 新建子节点挂上去
            node = node.children[idx]  # 走到该子节点
        node.is_end = True  # 末尾节点标记为单词结尾

    def search(self, word: str) -> bool:  # 查询单词，. 可以匹配任意字母
        def search(word, node):  # 内部递归函数：判断 word 能否从节点 node 继续匹配完
            for i in range(len(word)):  # 逐字符匹配
                c = word[i]  # 当前字符
                idx = ord(c) - ord('a')  # 字符映射成下标（. 的映射值只是占位，下面会先判断 c）
                if c != '.' and node.children[idx] is None:  # 普通字符但对应分支不存在，直接失败
                    return False  # 匹配失败
                if c == '.':  # 遇到通配符 .
                    for child in node.children:  # 枚举全部 26 个分支
                        if child is not None and search(word[i + 1 :], child):  # 该分支存在，且剩余部分能匹配
                            return True  # 有一条走通即成功
                    return False  # 所有分支都失败
                node = node.children[idx]  # 普通字符：走到对应子节点继续
            return node.is_end  # 字符全部匹配完，还需当前节点是单词结尾

        return search(word, self.trie)  # 从根节点开始匹配整个单词


# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)
