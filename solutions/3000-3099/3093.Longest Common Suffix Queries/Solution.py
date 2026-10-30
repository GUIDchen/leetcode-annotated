# 题目：3093. 最长公共后缀查询（Longest Common Suffix Queries）
# 思路：把所有容器串「倒序」插入字典树，每个结点记下经过它的串中最短的长度与对应下标（长度相同保留更早的下标）；查询时沿倒序尽量向下走，停住处的记录就是答案。
# 时间复杂度：O(Σ|wordsContainer| + Σ|wordsQuery|)，每个字符只走一步；空间复杂度：O(26 × Σ|wordsContainer|)，字典树结点开销。
class Trie:  # 倒序字典树：根结点代表空后缀
    __slots__ = ("children", "length", "idx")  # 限定属性集合，省内存并加快访问

    def __init__(self):  # 构造一个空结点
        self.children = [None] * 26  # 26 个小写字母对应的子结点
        self.length = inf  # 经过本结点的串的最短长度，inf 表示尚未记录
        self.idx = inf  # 该最短串在容器数组中的下标，inf 表示尚未记录

    def insert(self, w: str, i: int):  # 把下标为 i 的串 w 倒序插入
        node = self  # 从根结点开始
        if node.length > len(w):  # 根结点代表空后缀，也可能被这个串更新
            node.length = len(w)  # 记录更短的长度
            node.idx = i  # 记录该串下标
        for c in w[::-1]:  # w[::-1] 得到反转串，即从尾部往前遍历字符
            idx = ord(c) - ord("a")  # 字符映射到 0..25
            if node.children[idx] is None:  # 该分支不存在就先建出来
                node.children[idx] = Trie()  # 新建子结点
            node = node.children[idx]  # 走到子结点
            if node.length > len(w):  # 用当前串尝试更新该结点的记录
                node.length = len(w)  # 只有当前串更短才覆盖（等长时保留更早的下标）
                node.idx = i  # 记录下标

    def query(self, w: str) -> int:  # 查询串 w 的最长公共后缀对应的最优下标
        node = self  # 从根结点开始
        for c in w[::-1]:  # 从尾部往前遍历查询串
            idx = ord(c) - ord("a")  # 字符映射到 0..25
            if node.children[idx] is None:  # 再往下就没有公共后缀了
                break  # 停止深入，当前结点就是最长公共后缀所在
            node = node.children[idx]  # 继续深入
        return node.idx  # 返回该结点记录的最优下标（根结点对应空后缀）


class Solution:  # LeetCode 约定的题解类
    def stringIndices(  # 返回每个查询串对应的答案下标
        self, wordsContainer: List[str], wordsQuery: List[str]
    ) -> List[int]:
        trie = Trie()  # 建一棵空字典树
        for i, w in enumerate(wordsContainer):  # 遍历容器串及其下标
            trie.insert(w, i)  # 带着下标插入
        return [trie.query(w) for w in wordsQuery]  # 逐个查询并收集答案
