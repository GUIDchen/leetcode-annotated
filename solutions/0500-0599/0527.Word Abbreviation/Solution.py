# 题目：527. 单词缩写（Word Abbreviation）
# 思路：按「(长度, 末字母)」分组建 Trie，节点存经过的单词数；走到 cnt==1 的前缀即为最短唯一缩写，其余长度不足时保留原词。
# 时间复杂度：O(L²)，每个单词最多试 L 个前缀长度；空间复杂度：O(m·L)，Trie 存储所有字符。
class Trie:  # 字典树节点：记录公共前缀上经过的单词数量
    __slots__ = ["children", "cnt"]  # 用 __slots__ 固定属性，省掉每个节点的字典开销

    def __init__(self):  # 构造函数：初始化节点
        self.children = [None] * 26  # 26 个小写字母对应的子节点，全部为空
        self.cnt = 0  # 经过本节点的单词数

    def insert(self, w: str):  # 把一个单词插入 Trie
        node = self  # 从根节点开始向下走
        for c in w:  # 逐字符沿 Trie 下行
            idx = ord(c) - ord("a")  # 把字母映射成 0..25 的下标
            if not node.children[idx]:  # 该字母对应的子节点还不存在
                node.children[idx] = Trie()  # 新建一个节点接上去
            node = node.children[idx]  # 走到子节点
            node.cnt += 1  # 经过该节点的单词数加一

    def search(self, w: str) -> int:  # 求单词 w 的最短唯一前缀长度
        node = self  # 从根节点出发
        cnt = 0  # 已走过的字符数，也就是前缀长度
        for c in w:  # 逐字符沿 Trie 下行
            cnt += 1  # 前缀长度加一
            idx = ord(c) - ord("a")  # 把字母映射成 0..25 的下标
            node = node.children[idx]  # 走到对应的子节点
            if node.cnt == 1:  # 只有 w 自己经过这个前缀，说明前缀已唯一
                return cnt  # 返回最短唯一前缀的长度
        return len(w)  # 走完仍不唯一，只能在整个单词范围内缩写


class Solution:  # LeetCode 约定的题解类
    def wordsAbbreviation(self, words: List[str]) -> List[str]:  # words：待缩写的单词列表；返回每个单词对应的缩写
        tries = {}  # 分组键 (长度, 末字母) → 该分组共用的一棵 Trie
        for w in words:  # 第一遍：把所有单词按分组插入各自的 Trie
            m = len(w)  # 单词长度
            if (m, w[-1]) not in tries:  # 该分组还没有 Trie
                tries[(m, w[-1])] = Trie()  # 为这个分组新建一棵空 Trie
            tries[(m, w[-1])].insert(w)  # 把单词插入对应分组的 Trie
        ans = []  # 保存每个单词的缩写结果
        for w in words:  # 第二遍：按原始顺序逐个生成缩写
            cnt = tries[(len(w), w[-1])].search(w)  # 求该单词的最短唯一前缀长度
            ans.append(  # 追加缩写结果
                w if cnt + 2 >= len(w) else w[:cnt] + str(len(w) - cnt - 1) + w[-1]  # 缩写不如原词短（cnt+2>=len）时保留原词，否则拼成「前缀+省略字母数+末字母」
            )  # append 调用结束
        return ans  # 返回所有单词的缩写，顺序与原输入一致
