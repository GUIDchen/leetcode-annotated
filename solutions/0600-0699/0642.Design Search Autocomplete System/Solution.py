# 题目：642. 设计搜索自动补全系统（Design Search Autocomplete System）
# 核心思路：用 27 叉前缀树（26 个字母 + 1 个空格）保存历史句子，节点记录热度 v 与完整句子 w；每次输入沿前缀下行，DFS 收集子树里的句子，按热度降序、字典序升序取前 3。
# 时间复杂度：每次 input 为 O(L + m log m)，L 为当前前缀长度、m 为匹配句子数；空间复杂度：O(所有句子字符总数) 的前缀树节点。
class Trie:  # 前缀树节点（每个节点同时也是这棵子树的根）
    def __init__(self):  # 初始化一个节点
        self.children = [None] * 27  # 27 个孩子：26 个小写字母 + 1 个空格
        self.v = 0  # 该节点对应句子的热度（非句子结尾为 0）
        self.w = ''  # 该节点对应句子的完整文本

    def insert(self, w, t):  # 插入句子 w，热度增加 t
        node = self  # 从根节点开始
        for c in w:  # 逐字符向下建链
            idx = 26 if c == ' ' else ord(c) - ord('a')  # 空格映射到 26，字母映射到 0~25
            if node.children[idx] is None:  # 该字符对应的孩子还没建
                node.children[idx] = Trie()  # 新建节点挂上去
            node = node.children[idx]  # 走到孩子节点
        node.v += t  # 句子结尾节点累加热度
        node.w = w  # 记录完整句子，DFS 时可以直接取出

    def search(self, pref):  # 返回前缀 pref 对应的节点，找不到则返回 None
        node = self  # 从根节点开始
        for c in pref:  # 沿前缀逐字符下行
            idx = 26 if c == ' ' else ord(c) - ord('a')  # 与 insert 用同样的下标映射
            if node.children[idx] is None:  # 路径断开说明没有以该前缀开头的句子
                return None  # 直接返回 None
            node = node.children[idx]  # 继续下行
        return node  # 返回前缀末尾对应的节点


class AutocompleteSystem:  # 搜索自动补全系统
    def __init__(self, sentences: List[str], times: List[int]):  # sentences：历史句子；times：对应热度
        self.trie = Trie()  # 建立空前缀树
        for a, b in zip(sentences, times):  # 把历史句子逐一插入
            self.trie.insert(a, b)  # 按给定热度计入
        self.t = []  # 当前已经敲入的字符序列

    def input(self, c: str) -> List[str]:  # 输入一个字符（# 表示句子输入结束），返回热度最高的 3 个候选
        def dfs(node):  # 内部函数：收集以 node 为根的子树上所有句子
            if node is None:  # 空节点直接返回
                return  # 递归出口
            if node.v:  # 该节点是某个句子的结尾（热度非 0）
                res.append((node.v, node.w))  # 收集 (热度, 句子)
            for nxt in node.children:  # 递归所有孩子
                dfs(nxt)  # 深度优先展开

        if c == '#':  # 输入 # 表示一个句子输入完成
            s = ''.join(self.t)  # 拼出完整句子
            self.trie.insert(s, 1)  # 该句子热度加一
            self.t = []  # 清空当前输入缓存
            return []  # 按题意返回空列表

        res = []  # 存放匹配到的 (热度, 句子)
        self.t.append(c)  # 把新字符加入当前前缀
        node = self.trie.search(''.join(self.t))  # 沿前缀走到对应节点
        if node is None:  # 没有以该前缀开头的句子
            return res  # 返回空列表
        dfs(node)  # 收集该前缀下的所有句子
        res.sort(key=lambda x: (-x[0], x[1]))  # 热度降序、字典序升序排序
        return [v[1] for v in res[:3]]  # 取前 3 个句子的文本


# Your AutocompleteSystem object will be instantiated and called as such:
# obj = AutocompleteSystem(sentences, times)
# param_1 = obj.input(c)
