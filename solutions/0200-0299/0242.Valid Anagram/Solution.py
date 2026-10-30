# 题目：242. 有效的字母异位词（Valid Anagram）
# 思路：长度不同直接判否；否则用 Counter 统计 s 的字符频次，再逐个消耗 t 的字符，一旦出现负计数就失败。
# 时间复杂度：O(n)，两串各遍历一次；空间复杂度：O(1)，不同字符种类数最多 26。
class Solution:  # LeetCode 约定的题解类
    def isAnagram(self, s: str, t: str) -> bool:  # s、t 是待比较的两个字符串
        if len(s) != len(t):  # 长度不同一定不是异位词
            return False  # 直接返回失败
        cnt = Counter(s)  # 统计 s 中每个字符出现的次数
        for c in t:  # 逐个消耗 t 中的字符
            cnt[c] -= 1  # 对应字符的剩余计数减一
            if cnt[c] < 0:  # 计数变成负数说明该字符在 t 中出现得更多
                return False  # 提前返回失败
        return True  # 长度相同且计数从未为负，说明两边完全抵消
