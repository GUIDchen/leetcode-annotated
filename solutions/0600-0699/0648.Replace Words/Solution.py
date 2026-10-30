# 题目：648. 单词替换（Replace Words）
# 思路：先把所有词根建成字典树，再对句子中的每个单词沿树下行，遇到第一个词根结尾就替换为该最短词根。
# 时间复杂度：O(总字符数)，建树与查询都是每个字符走一步；空间复杂度：O(总词根字符数)，即字典树节点数。
class Trie:  # 字典树（前缀树）节点类
    def __init__(self):  # 构造一个空节点
        self.children = [None] * 26  # 26 个小写字母对应的子节点槽位，None 表示该分支不存在
        self.is_end = False  # 标记从根到本节点的路径是否构成一个完整词根

    def insert(self, w: str) -> None:  # 把词根 w 插入字典树
        node = self  # 游标从根节点开始
        for c in w:  # 逐个字符沿树下行
            idx = ord(c) - ord("a")  # 把字母换算成 0~25 的子节点下标
            if node.children[idx] is None:  # 该分支不存在时才需要新建节点
                node.children[idx] = Trie()  # 创建新节点并挂到当前节点下
            node = node.children[idx]  # 游标下移一位
        node.is_end = True  # 在词尾节点打上结束标记

    def search(self, w: str) -> str:  # 返回 w 的最短词根；没有匹配的词根时原样返回 w
        node = self  # 游标从根节点开始
        for i, c in enumerate(w, 1):  # i 从 1 开始计数，正好等于当前前缀的长度
            idx = ord(c) - ord("a")  # 当前字符对应的子节点下标
            if node.children[idx] is None:  # 前缀在树中中断，说明不存在可用的词根
                return w  # 无法替换，返回原单词
            node = node.children[idx]  # 游标下移一位
            if node.is_end:  # 命中词根结尾，且第一次命中即为最短词根
                return w[:i]  # 切出长度为 i 的前缀作为替换结果
        return w  # 整词走完仍没有词根结尾，返回原单词


class Solution:  # LeetCode 约定的题解类
    def replaceWords(self, dictionary: List[str], sentence: str) -> str:  # dictionary 是词根表，sentence 是待替换句子
        trie = Trie()  # 建一棵空字典树
        for w in dictionary:  # 逐个插入词根
            trie.insert(w)  # 把一个词根写入字典树
        return " ".join(trie.search(w) for w in sentence.split())  # 按空格切词，逐个替换后再用空格拼回句子
