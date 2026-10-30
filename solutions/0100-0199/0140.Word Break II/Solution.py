# 题目：140. 单词拆分 II（Word Break II）
# 思路：先用 26 叉字典树存下单词表，再从字符串头部 DFS 枚举所有可切分的前缀，回溯拼出全部句子。
# 时间复杂度：与可行方案数成正比（最坏指数级），单次前缀判定 O(L)；空间复杂度：O(m·L) 的字典树 + O(n) 递归栈。
class Trie:  # 字典树节点：用 26 个字母的定长数组存儿子，查询比哈希更快
    def __init__(self):  # 初始化一个字典树节点
        self.children = [None] * 26  # children[i] 对应第 i 个字母的子树，None 表示还没有这个分支
        self.is_end = False  # 标记从根走到这里是否构成一个完整单词

    def insert(self, word):  # 把一个单词插入字典树
        node = self  # 从当前节点（根）开始向下走
        for c in word:  # 逐个字符下行
            idx = ord(c) - ord('a')  # 把字符映射成 0..25 的下标
            if node.children[idx] is None:  # 该字母对应的分支还不存在
                node.children[idx] = Trie()  # 新建子节点占位
            node = node.children[idx]  # 指针下移到子节点
        node.is_end = True  # 单词走完，在末节点打上结束标记

    def search(self, word):  # 查询某个字符串是否恰好是字典中的完整单词
        node = self  # 同样从根节点出发
        for c in word:  # 逐字符沿树下行
            idx = ord(c) - ord('a')  # 字符转成数组下标
            if node.children[idx] is None:  # 路径断了，说明不存在这个前缀
                return False  # 不是字典里的单词，提前返回
            node = node.children[idx]  # 继续下移
        return node.is_end  # 路径走通，还要确认这里确实是单词结尾


class Solution:  # LeetCode 约定的题解类
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:  # s：待拆分字符串；wordDict：单词表；返回所有可能的句子
        def dfs(s):  # 返回把字符串 s 拆成单词后所有可能的「单词列表」组合
            if not s:  # 递归边界：空串
                return [[]]  # 空串对应一种空切法，返回只含空列表的结果
            res = []  # 收集当前 s 的所有切分方案
            for i in range(1, len(s) + 1):  # 枚举第一段的结束位置 i
                if trie.search(s[:i]):  # 前缀 s[:i] 是字典中的单词才值得继续往下切
                    for v in dfs(s[i:]):  # 递归求剩余部分 s[i:] 的所有切法
                        res.append([s[:i]] + v)  # 把首段与剩余的每种切法拼成一个新的切分序列
            return res  # 返回当前子问题的全部方案

        trie = Trie()  # 建一棵字典树来存放单词表
        for w in wordDict:  # 逐个单词插入
            trie.insert(w)  # 插入结束，之后的前缀判定都走字典树
        ans = dfs(s)  # 得到所有切分方案，每个方案是一个单词列表
        return [' '.join(v) for v in ans]  # 按题目要求用空格把单词连成句子
