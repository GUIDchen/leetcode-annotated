# 题目：676. 实现一个魔法字典（Implement Magic Dictionary）
# 思路：把词表建成字典树，查询时 DFS 逐字符匹配并记录已用掉的替换次数 diff，走完词尾时恰好替换一次且落在单词结尾才算命中。
# 时间复杂度：插入 O(L)；查询最坏 O(26 * L * 26)，每个位置允许一次岔路；空间复杂度：O(总字符数 * 26)，字典树节点开销。
class Trie:  # 字典树节点
    __slots__ = "children", "is_end"  # 限定实例属性，省去 __dict__ 以节省内存

    def __init__(self):  # 构造节点
        self.children: List[Optional[Trie]] = [None] * 26  # 26 个子节点，下标是字符相对 'a' 的偏移
        self.is_end = False  # 标记从根到此处是否构成完整单词

    def insert(self, w: str) -> None:  # 把一个单词插入字典树
        node = self  # 从根节点开始
        for c in w:  # 逐字符向下
            idx = ord(c) - ord("a")  # 计算字符对应的孩子下标
            if node.children[idx] is None:  # 该分支还不存在
                node.children[idx] = Trie()  # 新建一个节点补上
            node = node.children[idx]  # 走到对应的孩子节点
        node.is_end = True  # 最后一个字符处标记单词结束

    def search(self, w: str) -> bool:  # 判断是否存在恰好替换一个字母后等于 w 的单词
        def dfs(i: int, node: Optional[Trie], diff: int) -> bool:  # i 是字符下标，diff 是已用掉的替换次数
            if i == len(w):  # 已经走完整个待查串
                return diff == 1 and node.is_end  # 必须恰好替换一次，且落在某个单词结尾
            j = ord(w[i]) - ord("a")  # 当前字符对应的孩子下标
            if node.children[j] and dfs(i + 1, node.children[j], diff):  # 不走岔路：原样匹配当前字符继续往下
                return True  # 后续匹配成功即返回
            return diff == 0 and any(  # 还没用过替换机会，就在当前位置换一个字母再试
                node.children[k] and dfs(i + 1, node.children[k], 1)  # 该字母分支存在且用掉替换机会后能匹配成功
                for k in range(26)  # 枚举 26 个可能的替换字母
                if k != j  # 跳过与原字符相同的那个
            )

        return dfs(0, self, 0)  # 从根节点、第 0 个字符、还没替换过开始搜索


class MagicDictionary:  # 题目要求的魔法字典类
    def __init__(self):  # 构造字典
        self.trie = Trie()  # 创建空的字典树根节点

    def buildDict(self, dictionary: List[str]) -> None:  # 用给定词表构建字典
        for w in dictionary:  # 逐个单词
            self.trie.insert(w)  # 插入字典树

    def search(self, searchWord: str) -> bool:  # 判断能否由字典中恰好替换一个字母得到
        return self.trie.search(searchWord)  # 交给字典树去搜索


# Your MagicDictionary object will be instantiated and called as such:
# obj = MagicDictionary()
# obj.buildDict(dictionary)
# param_2 = obj.search(searchWord)
