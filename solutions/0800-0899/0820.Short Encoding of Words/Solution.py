# 题目：820. 单词的压缩编码（Short Encoding of Words）
# 思路：互为后缀的单词可以共用一段编码，于是把所有单词倒序插入字典树；建树后每个叶子到根的路径长度之和就是答案（根计 1，代表结尾的 '#'）。
# 时间复杂度：O(Σ|w|)，Σ|w| 为所有单词总长度；空间复杂度：O(Σ|w|)，字典树节点数不超过总长度。
class Trie:  # 字典树节点
    def __init__(self) -> None:  # 构造函数
        self.children = [None] * 26  # 26 个小写字母的孩子指针，初始都为空


class Solution:  # LeetCode 约定的题解类
    def minimumLengthEncoding(self, words: List[str]) -> int:  # words：待编码的单词列表
        root = Trie()  # 字典树根节点
        for w in words:  # 逐个单词处理
            cur = root  # 从根出发
            for c in w[::-1]:  # 倒序遍历单词字符，让「后缀相同」变成「公共前缀」
                idx = ord(c) - ord("a")  # 字符映射到 0..25 的下标
                if cur.children[idx] == None:  # 孩子节点不存在则新建
                    cur.children[idx] = Trie()  # 新建节点
                cur = cur.children[idx]  # 向下走一层
        return self.dfs(root, 1)  # 从根开始统计，根层长度记为 1（末尾的 '#' 也算一个字符）

    def dfs(self, cur: Trie, l: int) -> int:  # cur：当前节点；l：当前长度（含 '#'）
        isLeaf, ans = True, 0  # isLeaf 标记是否为叶子；ans 累计子树总长度
        for i in range(26):  # 遍历 26 个孩子
            if cur.children[i] != None:  # 该孩子存在
                isLeaf = False  # 有孩子就不是叶子
                ans += self.dfs(cur.children[i], l + 1)  # 递归累加，深度加 1
        if isLeaf:  # 叶子说明有单词在这里结束
            ans += l  # 加上该单词的编码长度
        return ans  # 返回子树总长度
