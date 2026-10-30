# 题目：1065. 字符串的索引对（Index Pairs of a String）
# 思路：把单词表转成集合，用列表推导式枚举 text 的所有子串，命中单词就产出一对 [起点, 终点] 下标。
# 时间复杂度：O(n^2 · L)，枚举 O(n^2) 个子串且切片/哈希耗 O(L)；空间复杂度：O(总字符数)，存集合与答案。
class Solution:  # LeetCode 约定的题解类
    def indexPairs(self, text: str, words: List[str]) -> List[List[int]]:  # text：主串；words：待查找单词表，返回所有命中的 [起始下标, 结束下标]
        words = set(words)  # 转成集合，让子串是否属于单词表的判断变成 O(1) 平均复杂度
        n = len(text)  # 主串长度，即子串起止下标的范围
        return [  # 列表推导式直接构造答案：外层枚举起点 i，内层枚举终点 j
            [i, j] for i in range(n) for j in range(i, n) if text[i : j + 1] in words  # 切片 text[i : j + 1] 即子串，属于单词集合就产出一对下标；i、j 递增保证输出已排序
        ]  # 推导式结束，整张列表作为返回值
