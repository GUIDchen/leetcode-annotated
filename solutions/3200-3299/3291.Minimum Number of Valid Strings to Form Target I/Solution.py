# 题目：3291. 形成目标字符串需要的最少字符串数 I（Minimum Number of Valid Strings to Form Target I）
# 思路：把 words 建成字典树，记 dfs(i) 为拼出 target[i..] 的最少串数，枚举所有字典树可匹配的前缀长度 j-i+1 取最小值。
# 时间复杂度：O(n^2 + L)，n 为 target 长度、L 为 words 总字符数；空间复杂度：O(n + L)，用于缓存与字典树。
def min(a: int, b: int) -> int:  # 手写 min 函数，覆盖内置 min（doocs 原题解就是这么写的）
    return a if a < b else b  # 返回两个参数中较小的那个


class Trie:  # 字典树节点：判断 target 的某段前缀是否在 words 中
    def __init__(self):  # 构造 26 个小写字母子节点
        self.children: List[Optional[Trie]] = [None] * 26  # children[i] 表示字母 i 的子节点，None 表示没有这条边

    def insert(self, w: str):  # 把字符串 w 插入字典树
        node = self  # 从根节点开始
        for i in map(lambda c: ord(c) - 97, w):  # 把每个字符映射成 [0,25] 的下标，逐个向下建链
            if node.children[i] is None:  # 该字母的子节点还不存在
                node.children[i] = Trie()  # 新建一个节点挂上去
            node = node.children[i]  # 下移一层，继续插入下一个字符


class Solution:  # LeetCode 约定的题解类
    def minValidStrings(self, words: List[str], target: str) -> int:  # words：候选串列表；target：待拼出的目标串
        @cache  # 记忆化装饰器：同一个 i 只算一次
        def dfs(i: int) -> int:  # i 是 target 中当前要拼到的下标
            if i >= n:  # 已经拼到 target 末尾
                return 0  # 不需要更多串
            node = trie  # 从字典树根开始匹配
            ans = inf  # 先用无穷大表示「拼不出来」
            for j in range(i, n):  # 枚举以 i 开头的所有可能匹配长度
                k = ord(target[j]) - 97  # 当前字符对应的子节点下标
                if node.children[k] is None:  # 字典树里没有这条边
                    break  # 更长的前缀也不可能匹配，直接停止
                node = node.children[k]  # 沿字典树向下走一层，前缀又长一位
                ans = min(ans, 1 + dfs(j + 1))  # 用 target[i..j] 作为一个串，再拼后面的部分
            return ans  # 返回从 i 开始拼所需的最少串数

        trie = Trie()  # 建一棵空字典树
        for w in words:  # 把所有候选串插入字典树
            trie.insert(w)  # 插入单个候选串
        n = len(target)  # 目标串长度（dfs 通过闭包使用，因此必须在调用前定义）
        ans = dfs(0)  # 从 target 开头开始拼
        return ans if ans < inf else -1  # 拼不出来时按题意返回 -1
