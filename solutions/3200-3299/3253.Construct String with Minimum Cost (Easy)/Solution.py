# 题目：3253. 最小代价构造字符串（简单）（Construct String with Minimum Cost (Easy)）
# 思路：先把所有单词及其代价插入字典树（同一单词保留最小代价），再对 target 做带 @cache 记忆化的 DFS：枚举从 i 开始能匹配的单词，取「单词代价 + 剩余部分代价」的最小值。
# 时间复杂度：O(n² + Σ|word|)，n 为 target 长度；空间复杂度：O(n + Σ|word|)，用于字典树与记忆化。
class Trie:  # 字典树：把所有单词挂到树上，便于沿 target 逐字符匹配
    def __init__(self):  # 构造一个空的字典树节点
        self.children: List[Optional[Trie]] = [None] * 26  # 26 个小写字母子节点，默认全部为 None
        self.cost = inf  # 以本节点结尾的单词的最小代价，默认视为不可用

    def insert(self, word: str, cost: int):  # 插入单词，并更新结尾节点的最小代价
        node = self  # 从根节点开始向下插入
        for c in word:  # 逐个字符沿树下行
            idx = ord(c) - ord("a")  # 把字母映射到 0..25 的分支下标
            if node.children[idx] is None:  # 该分支还不存在时才需要新建节点
                node.children[idx] = Trie()  # 新建一个字典树节点挂在当前位置
            node = node.children[idx]  # 走到对应的子节点，继续处理下一个字符
        node.cost = min(node.cost, cost)  # 同一单词出现多次时只保留最小代价


class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, target: str, words: List[str], costs: List[int]) -> int:  # target：目标串；words/costs：可用单词及其代价；返回最小拼接代价
        @cache  # 记忆化装饰器：同一个 i 只计算一次
        def dfs(i: int) -> int:  # 求从下标 i 开始拼出 target[i..] 的最小代价
            if i >= len(target):  # 已经匹配到末尾
                return 0  # 不需要再花费，代价为 0
            ans = inf  # 先假设从 i 开始无法拼完
            node = trie  # 从字典树根开始，沿 target[j] 逐字符向下走
            for j in range(i, len(target)):  # 枚举当前单词的结束位置 j
                idx = ord(target[j]) - ord("a")  # 当前字符对应的分支下标
                if node.children[idx] is None:  # 字典树中没有这条路径，说明以 i 开头的更长的串也不存在
                    return ans  # 直接返回当前最优值
                node = node.children[idx]  # 沿字符继续下走
                ans = min(ans, node.cost + dfs(j + 1))  # 用「结束于 j 的单词代价 + 剩余部分的最小代价」更新答案
            return ans  # 返回从 i 开始的最小代价

        trie = Trie()  # 建字典树的根节点（闭包变量，供 dfs 使用）
        for word, cost in zip(words, costs):  # 把所有单词按顺序插入字典树
            trie.insert(word, cost)  # 插入第 i 个单词及其代价
        ans = dfs(0)  # 从下标 0 开始拼出整个 target
        return ans if ans < inf else -1  # 仍为 inf 说明无法拼出，按题目要求返回 -1
