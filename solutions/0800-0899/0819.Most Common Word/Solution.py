# 题目：819. 最常见的单词（Most Common Word）
# 思路：先把段落整体转小写，用正则切出所有连续小写字母，用 Counter 统计词频，再按词频从高到低找第一个不属于禁用词的单词。
# 时间复杂度：O(n + b)，n 为段落长度、b 为禁用词总长；空间复杂度：O(n + b)，用于词频表与禁用集合。
class Solution:  # LeetCode 约定的题解类
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:  # paragraph：整段文本；banned：禁用词列表
        s = set(banned)  # 禁用词放进集合，便于 O(1) 判断
        p = Counter(re.findall('[a-z]+', paragraph.lower()))  # 先整体转小写，再用正则切出所有连续小写字母，最后用 Counter 统计词频
        return next(word for word, _ in p.most_common() if word not in s)  # 按词频从高到低遍历，返回第一个不属于禁用词的单词
