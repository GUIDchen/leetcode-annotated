# 题目：1804. 实现 Trie（前缀树）II（Implement Trie II (Prefix Tree)）
# 思路：每个节点保存 v（以该节点结尾的单词数）与 pv（经过该节点的单词数，即该前缀的单词数）；插入与删除沿路径增减计数，查询先定位节点再读计数。
# 时间复杂度：每次操作 O(L)，L 为单词长度；空间复杂度：O(总字符数)，每个字符最多对应一个新节点。
class Trie:  # LeetCode 约定的前缀树类
    def __init__(self):  # 构造函数：26 个子节点为空，单词计数与前缀计数都为 0
        self.children = [None] * 26  # 26 个字母对应的子节点，下标 0~25 代表 a~z
        self.v = self.pv = 0  # v 为以本节点结尾的单词数，pv 为经过本节点的单词数（前缀计数）

    def insert(self, word: str) -> None:  # 插入一个单词
        node = self  # 从根节点开始向下走
        for c in word:  # 逐字符沿路径向下建链
            idx = ord(c) - ord('a')  # 把字母映射成 0~25 的下标
            if node.children[idx] is None:  # 该字母对应的子节点还不存在
                node.children[idx] = Trie()  # 新建一个子节点挂上去
            node = node.children[idx]  # 走到该字母对应的子节点
            node.pv += 1  # 路径上每个节点的前缀计数加一
        node.v += 1  # 单词末尾节点的结尾计数加一

    def countWordsEqualTo(self, word: str) -> int:  # 返回与 word 完全相同的单词个数
        node = self.search(word)  # 先定位到 word 末尾对应的节点
        return 0 if node is None else node.v  # 节点存在返回结尾计数 v，否则返回 0

    def countWordsStartingWith(self, prefix: str) -> int:  # 返回以 prefix 为前缀的单词个数
        node = self.search(prefix)  # 先定位到 prefix 末尾对应的节点
        return 0 if node is None else node.pv  # 节点存在返回前缀计数 pv，否则返回 0

    def erase(self, word: str) -> None:  # 删除一个单词（题目保证该单词存在）
        node = self  # 从根节点开始向下走
        for c in word:  # 逐字符沿路径向下
            idx = ord(c) - ord('a')  # 把字母映射成 0~25 的下标
            node = node.children[idx]  # 走到该字母对应的子节点
            node.pv -= 1  # 沿途前缀计数减一
        node.v -= 1  # 末尾节点结尾计数减一

    def search(self, word):  # 沿字符路径查找，返回 word 末尾对应的节点；路径断了返回 None
        node = self  # 从根节点开始查找
        for c in word:  # 逐字符向下
            idx = ord(c) - ord('a')  # 把字母映射成 0~25 的下标
            if node.children[idx] is None:  # 路径断了说明没有这个单词/前缀
                return None  # 返回 None 表示不存在
            node = node.children[idx]  # 走到该字母对应的子节点
        return node  # 返回 word 末尾对应的节点


# 下面是 LeetCode 模板给出的调用示例，原本就是注释，原样保留
# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.countWordsEqualTo(word)
# param_3 = obj.countWordsStartingWith(prefix)
# obj.erase(word)
