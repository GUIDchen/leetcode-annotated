# 题目：2451. 差值数组不同的字符串（Odd String Difference）
# 思路：用 pairwise 取相邻字符对，把「相邻字符差值元组」当作字典键分组，只出现一次的那组对应的字符串就是答案。
# 时间复杂度：O(L)，L 为所有字符串的总长度；空间复杂度：O(L)，字典保存全部差值元组与字符串引用。
class Solution:  # LeetCode 约定的题解类
    def oddString(self, words: List[str]) -> str:  # words：长度全部相同的字符串数组，返回差值数组与众不同的那个字符串
        d = defaultdict(list)  # 字典：键是差值元组，值是该差值元组对应的字符串列表，list 默认工厂省去判空
        for s in words:  # 逐个处理输入字符串
            t = tuple(ord(b) - ord(a) for a, b in pairwise(s))  # pairwise 产生相邻字符对，ord 相减得到可哈希的差值元组
            d[t].append(s)  # 以差值元组为键分组，把原串追加到对应列表
        return next(ss[0] for ss in d.values() if len(ss) == 1)  # 找到长度为 1 的分组，返回其中唯一的那个字符串
