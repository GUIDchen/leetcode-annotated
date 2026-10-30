# 题目：2416. 字符串的前缀分数和（Sum of Prefix Scores of Strings）
# 思路：把所有单词插入同一棵字典树，每个结点记录「有多少个单词经过它」；查询某个单词时，沿途累加各前缀结点的经过次数，就是该单词的前缀分数和。
# 时间复杂度：O(L)，L 为所有单词字符总数，建树与逐个查询各扫描一遍；空间复杂度：O(L)，字典树结点数不超过字符总数。
class Trie:  # 字典树结点：26 个子结点 + 经过该结点的单词数
    __slots__ = "children", "cnt"  # 限定实例属性，省掉 __dict__，让结点更省内存

    def __init__(self):  # 初始化一个空结点
        self.children = [None] * 26  # 26 个小写字母对应的子结点，None 表示还没有
        self.cnt = 0  # cnt：有多少个单词经过当前结点

    def insert(self, w):  # 把单词 w 插入字典树，并给沿途每个前缀结点计数加一
        node = self  # 从根结点出发向下走
        for c in w:  # 逐个字符沿树下行
            idx = ord(c) - ord("a")  # 把字符映射为 0..25 的下标
            if node.children[idx] is None:  # 该字符对应的子结点还不存在
                node.children[idx] = Trie()  # 新建结点并挂在当前位置下
            node = node.children[idx]  # 走到子结点上，代表前缀又长了一个字符
            node.cnt += 1  # 当前单词经过了该前缀，计数加一

    def search(self, w):  # 查询单词 w 的「所有前缀出现次数」之和
        node = self  # 从根结点出发
        ans = 0  # 累加结果
        for c in w:  # 逐个字符沿树下行
            idx = ord(c) - ord("a")  # 字符到子结点下标
            if node.children[idx] is None:  # 前缀链断开（本题每个单词都插入过，不会发生）
                return ans  # 只能返回已经累加到的部分
            node = node.children[idx]  # 进入该前缀对应的结点
            ans += node.cnt  # 该前缀的出现次数计入答案
        return ans  # 返回完整的前缀分数和


class Solution:  # LeetCode 约定的题解类
    def sumPrefixScores(self, words: List[str]) -> List[int]:  # words：输入单词数组
        trie = Trie()  # 建一棵被所有单词共享的字典树
        for w in words:  # 第一遍：把所有单词都插入字典树
            trie.insert(w)  # 插入后每个前缀的出现次数就统计完毕
        return [trie.search(w) for w in words]  # 第二遍：按原顺序逐个查询并组成答案
