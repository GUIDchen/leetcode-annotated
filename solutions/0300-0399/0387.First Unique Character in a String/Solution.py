# 题目：387. 字符串中的第一个唯一字符（First Unique Character in a String）
# 思路：Counter 统计每个字母出现次数，再从左到右找第一个计数为 1 的位置。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，字母表最多 26 个键。
class Solution:  # 题解类
    def firstUniqChar(self, s: str) -> int:  # s 是只含小写字母的字符串，返回第一个不重复字符的下标
        cnt = Counter(s)  # 一次统计出每个字母的出现次数
        for i, c in enumerate(s):  # 再按原顺序同时取得下标 i 与字符 c
            if cnt[c] == 1:  # 只出现一次，就是第一个唯一字符
                return i  # 返回它的下标
        return -1  # 扫完都没有唯一字符，按题目约定返回 -1
