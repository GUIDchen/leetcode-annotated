# 题目：2278. 字母在字符串中的百分比（Percentage of Letter in String）
# 思路：统计 letter 在 s 中出现的次数，乘 100 后整除字符串长度，向下取整。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def percentageLetter(self, s: str, letter: str) -> int:  # s 为输入字符串，letter 为要统计的字母
        return s.count(letter) * 100 // len(s)  # 出现次数先乘 100，再用 // 整除长度，保证结果是向下取整的整数
