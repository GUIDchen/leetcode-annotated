# 题目：288. 单词的唯一缩写（Unique Word Abbreviation）—— 判断某单词的缩写是否唯一，即该缩写没对应词典中的其它单词。
# 核心思路：构造时把词典按缩写分组（缩写 -> 单词集合）；查询时看该缩写下是否只存在目标单词自己。
# 时间复杂度：构造 O(总字符数)，单次查询 O(1) 期望；空间复杂度：O(总字符数)，字典存下全部单词。
class ValidWordAbbr:  # 设计类：构造阶段建索引，查询阶段只查表
    def __init__(self, dictionary: List[str]):  # dictionary：初始化词典
        self.d = defaultdict(set)  # 缩写 -> 出现过的单词集合；defaultdict(set) 省去每次判空
        for s in dictionary:  # 遍历词典中的每个单词
            self.d[self.abbr(s)].add(s)  # 按缩写归档，set 自动去重

    def isUnique(self, word: str) -> bool:  # 判断 word 的缩写是否唯一
        s = self.abbr(word)  # 先算出待查询单词的缩写
        return s not in self.d or all(word == t for t in self.d[s])  # 缩写不存在 → 唯一；否则要求该缩写下所有单词都等于 word 本身

    def abbr(self, s: str) -> str:  # 缩写规则：长度 < 3 时保持原样
        return s if len(s) < 3 else s[0] + str(len(s) - 2) + s[-1]  # 首字母 + 中间字符个数 + 末字母


# 下面是 LeetCode 生成的调用代码说明，保留原样，仅作提示
# Your ValidWordAbbr object will be instantiated and called as such:
# obj = ValidWordAbbr(dictionary)
# param_1 = obj.isUnique(word)
