# 题目：2309. 兼具大小写的最好英文字母（Greatest English Letter in Upper and Lower Case）
# 思路：先把字符串去重成集合，再从 Z 到 A 倒序枚举，第一个大小写都存在的字母就是答案。
# 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(26)，集合最多存 52 个不同字符。
class Solution:  # LeetCode 约定的题解类
    def greatestLetter(self, s: str) -> str:  # s 仅含英文字母，返回兼具大小写的最好字母
        ss = set(s)  # 去重成集合，便于 O(1) 判断某字符是否出现
        for c in ascii_uppercase[::-1]:  # 从 Z 倒序枚举到 A，保证优先得到字典序最大的字母
            if c in ss and c.lower() in ss:  # 大写形式与小写形式都出现过才有效
                return c  # 该字母符合条件，立即返回
        return ''  # 没有满足条件的字母，返回空串
