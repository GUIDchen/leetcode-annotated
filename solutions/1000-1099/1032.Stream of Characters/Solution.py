# 题目：1032. 字符流（Stream of Characters）
# 思路：把每个字典单词倒序插入前缀树，使「字符流后缀」对应「树上根到某节点的路径」；查询时从末尾向前走，遇到结束标记即命中。
# 时间复杂度：建树 O(L*m)，每次 query O(L)，L 为单词最大长度（≤200）；空间复杂度：O(L*m)，树节点总数。
class Trie:  # 前缀树（字典树）：以「倒序单词」建树，便于从字符流末尾往前匹配
    def __init__(self):  # 构造一个空节点
        self.children = [None] * 26  # 26 个小写字母对应的孩子指针，先全部置空
        self.is_end = False  # 标记「从根走到该节点的路径」是否恰好是一个完整单词

    def insert(self, w: str):  # 倒序插入单词：从单词末尾开始建路径
        node = self  # 从根节点开始
        for c in w[::-1]:  # 逆序切片遍历字符
            idx = ord(c) - ord('a')  # 字母映射为 0..25 的孩子下标
            if node.children[idx] is None:  # 这条分支还不存在
                node.children[idx] = Trie()  # 新建子节点补上这条边
            node = node.children[idx]  # 下行到子节点，继续插入下一个字符
        node.is_end = True  # 在末节点打上「单词结束」标记

    def search(self, w: List[str]) -> bool:  # 从 w 的末尾往前匹配：沿途遇到 is_end 就说明有单词是当前字符流的后缀
        node = self  # 从根节点开始匹配
        for c in w[::-1]:  # 逆序遍历（字符流的后缀顺序正好是倒序前缀）
            idx = ord(c) - ord('a')  # 当前字符对应的分支下标
            if node.children[idx] is None:  # 树里没有这条边，后缀不可能再匹配到任何单词
                return False  # 直接判定不存在
            node = node.children[idx]  # 沿边下行一个字符
            if node.is_end:  # 走到了某个单词的末尾节点
                return True  # 说明当前后缀恰好等于字典中的某个单词
        return False  # 遍历完仍未命中，返回 False


class StreamChecker:  # 字符流查询器：每来一个字符，判断当前流是否存在某个字典单词作为后缀
    def __init__(self, words: List[str]):  # 用字典 words 构建倒序前缀树，并准备一个累积字符流
        self.trie = Trie()  # 所有单词共用一棵倒序前缀树
        self.cs = []  # 累积已经读入的字符流（新字符从尾部追加，查询时取末尾一段）
        self.limit = 201  # 单词长度上限 200，因此查询时最多回看 201 个字符即可
        for w in words:  # 逐个单词建树
            self.trie.insert(w)  # 倒序插入

    def query(self, letter: str) -> bool:  # 每读入一个字符就查询一次，返回是否存在后缀命中
        self.cs.append(letter)  # 把新字符追加到字符流末尾
        return self.trie.search(self.cs[-self.limit :])  # 只截取最近 limit 个字符去匹配，避免字符流无限增长导致变慢


# Your StreamChecker object will be instantiated and called as such:
# obj = StreamChecker(words)
# param_1 = obj.query(letter)
