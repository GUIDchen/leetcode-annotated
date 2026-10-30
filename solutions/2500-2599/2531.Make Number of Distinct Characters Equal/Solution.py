# 题目：2531. 使字符串中不同字符的数目相等（Make Number of Distinct Characters Equal）
# 核心思路：用 Counter 统计两串频次与不同字符数，枚举交换的字母对，按「失去是否归零、得到是否新增」的增量公式判断能否相等。
# 时间复杂度：O(n + m + d1 × d2)，d 为不同字符数且不超过 26；空间复杂度：O(1)，最多 26 个计数。
class Solution:  # LeetCode 约定的题解类
    def isItPossible(self, word1: str, word2: str) -> bool:  # 判断能否只交换 word1、word2 之间的一对字符，使两串的不同字符数目相等
        cnt1 = Counter(word1)  # word1 的字母频次表
        cnt2 = Counter(word2)  # word2 的字母频次表
        x, y = len(cnt1), len(cnt2)  # 两串当前的不同字符数就是频次表的键数
        for c1, v1 in cnt1.items():  # 枚举从 word1 中拿去交换的字母 c1 及其频次 v1
            for c2, v2 in cnt2.items():  # 枚举从 word2 中拿去交换的字母 c2 及其频次 v2
                if c1 == c2:  # 交换同一个字母，两串的内容其实完全没变
                    if x == y:  # 原本不同字符数就相等
                        return True  # 直接可行
                else:  # 交换的是不同字母，需要重新推算两边的不同字符数
                    a = x - (v1 == 1) + (cnt1[c2] == 0)  # word1 失去 c1（唯一一个才减 1）、得到 c2（原本没有才加 1）
                    b = y - (v2 == 1) + (cnt2[c1] == 0)  # word2 失去 c2、得到 c1，布尔值直接当 0/1 参与运算
                    if a == b:  # 交换后两边不同字符数目相等
                        return True  # 找到一种可行交换
        return False  # 所有字母对都试过仍无解
