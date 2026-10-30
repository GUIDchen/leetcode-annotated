# 题目：1657. 确定两个字符串是否接近（Determine if Two Strings Are Close）
# 思路：接近的充要条件是字符集合相同，且字符出现次数构成的多重集合相同；因此比较两个 Counter 的 values 排序结果与 keys 集合。
# 时间复杂度：O(n + k log k)，k ≤ 26；空间复杂度：O(k)，两个计数器。
class Solution:  # LeetCode 约定的题解类
    def closeStrings(self, word1: str, word2: str) -> bool:  # word1、word2 是待比较的两个字符串
        cnt1, cnt2 = Counter(word1), Counter(word2)  # 分别统计两个串的字符频次
        return sorted(cnt1.values()) == sorted(cnt2.values()) and set(  # 频次的多重集合相同且字符集合也相同，才是「接近」
            cnt1.keys()
        ) == set(cnt2.keys())  # 换行只是排版，这里继续比较两个字符集合是否相等
