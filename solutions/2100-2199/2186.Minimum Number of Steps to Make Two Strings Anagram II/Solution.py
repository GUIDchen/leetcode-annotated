# 题目：2186. 制造字母异位词的最小步骤数 II（Minimum Number of Steps to Make Two Strings Anagram II）
# 思路：用 Counter 记录 s 的字母频次，再减去 t 的字母频次；正差表示 s 多出（删除），负差表示 s 缺少（补充），步数取绝对值之和。
# 时间复杂度：O(|s| + |t|)；空间复杂度：O(26) = O(1)。
class Solution:  # LeetCode 约定的题解类
    def minSteps(self, s: str, t: str) -> int:  # s、t：两个待比较的字符串
        cnt = Counter(s)  # 用 s 的字符频次初始化计数器
        for c in t:  # 遍历 t 的每个字符
            cnt[c] -= 1  # t 中出现一次就减一，差值可正可负
        return sum(abs(v) for v in cnt.values())  # 正差需删除、负差需补充，步数都是绝对值之和
