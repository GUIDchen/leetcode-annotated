# 题目：472. 连接词（Concatenated Words）
# 思路：把所有单词按长度升序处理，边处理边插入字典树；对当前单词用 DFS 在 Trie 上枚举可切分的词根，能切完即为连接词。
# 时间复杂度：O(L^2) 量级（L 为单词长度，每个词 DFS 枚举切分点并沿 Trie 前进）；空间复杂度：O(总字符数)，即字典树的节点数。
class Trie:  # 字典树节点，用于快速判断某个前缀是否是已见过的完整单词
    def __init__(self):  # 构造函数：初始化节点的孩子与结尾标记
        self.children = [None] * 26  # 26 个孩子位，分别对应字母 a~z
        self.is_end = False  # 标记「从根走到本节点」是否构成一个完整单词

    def insert(self, w):  # 把单词 w 插入字典树
        node = self  # 从根节点开始往下走
        for c in w:  # 逐字符遍历单词
            idx = ord(c) - ord('a')  # 把字符映射成 0~25 的下标
            if node.children[idx] is None:  # 该字母的孩子还不存在
                node.children[idx] = Trie()  # 新建一个节点接上
            node = node.children[idx]  # 下移到对应孩子
        node.is_end = True  # 最后一个字符对应的节点标记为单词结尾


class Solution:  # LeetCode 约定的题解类
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:  # words 是给定的单词表
        def dfs(w):  # 判断 w 能否由 Trie 中已有的单词拼接而成
            if not w:  # 空串说明已经全部切分成功
                return True  # 是递归的终止条件
            node = trie  # 从 Trie 根节点开始匹配前缀
            for i, c in enumerate(w):  # 逐字符沿 Trie 向下走，i 是当前字符下标
                idx = ord(c) - ord('a')  # 当前字符对应的下标
                if node.children[idx] is None:  # 前缀在 Trie 中不存在
                    return False  # 这条切分路走不通
                node = node.children[idx]  # 下移到对应孩子
                if node.is_end and dfs(w[i + 1 :]):  # 前 i+1 个字符是完整词根，递归检查剩余后缀
                    return True  # 后缀也能切分，整体成功
            return False  # 所有切分点都失败，该单词不是连接词

        trie = Trie()  # 全局字典树，边处理单词边累积收集
        ans = []  # 收集所有连接词
        words.sort(key=lambda x: len(x))  # 按长度升序排序，保证拼接所需的词根已插入 Trie
        for w in words:  # 依次处理每个单词
            if dfs(w):  # 能在 Trie 上被完整切分成若干词根
                ans.append(w)  # 是连接词，加入答案
            else:  # 不能切分说明它是「词根」
                trie.insert(w)  # 把它加入字典树，供更长的单词拆分时使用
        return ans  # 返回全部连接词
