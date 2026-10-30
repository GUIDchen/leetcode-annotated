# 题目：745. 前缀和后缀搜索（Prefix and Suffix Search）
# 核心思路：预处理时枚举每个单词的全部（前缀, 后缀）元组存进字典并映射到下标，后出现的下标覆盖前面的；查询直接查字典。
# 时间复杂度：预处理 O(Σ|w|^2)，单次查询 O(1)；空间复杂度：O(Σ|w|^2)，保存所有前缀后缀组合。
class WordFilter:  # 题目要求的类：构造时建表，查询走 f 方法
    def __init__(self, words: List[str]):  # 构造函数：预处理 words 的所有前缀/后缀组合
        self.d = {}  # 字典：键是（前缀, 后缀）元组，值是满足条件的最大单词下标
        for k, w in enumerate(words):  # k 就是下标，遍历顺序保证更靠后的更大下标覆盖前面的
            n = len(w)  # 单词长度，作为前缀长度与后缀起点的枚举上界
            for i in range(n + 1):  # i 为前缀长度，取 0..n，覆盖空前缀到整串
                a = w[:i]  # 切出长度为 i 的前缀
                for j in range(n + 1):  # j 为后缀起点，取 0..n，覆盖整串到空后缀
                    b = w[j:]  # 从 j 切到末尾得到后缀
                    self.d[(a, b)] = k  # 记录组合对应的下标，重复组合被更大的 k 覆盖

    def f(self, pref: str, suff: str) -> int:  # 查询同时满足前缀 pref、后缀 suff 的最大下标
        return self.d.get((pref, suff), -1)  # 命中返回下标，否则返回默认值 -1 表示不存在


# 下面三行是 LeetCode 判题器的调用示例注释，说明对象如何被构造与查询（原注释保持不动）
# Your WordFilter object will be instantiated and called as such:
# obj = WordFilter(words)
# param_1 = obj.f(pref,suff)
