# 题目：3120. 统计特殊字母的数量 I（Count the Number of Special Characters I）
# 思路：把字符串转成集合，再枚举 26 组「小写、大写」字母，两者都在集合中就给答案加一。
# 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(1)，集合最多存 52 个字符。
class Solution:  # LeetCode 约定的题解类
    def numberOfSpecialChars(self, word: str) -> int:  # word：输入字符串，返回大小写都出现过的字母个数
        s = set(word)  # 去重后的字符集合，查找是 O(1)
        return sum(a in s and b in s for a, b in zip(ascii_lowercase, ascii_uppercase))  # 逐对枚举大小写字母，两个都在集合里就贡献 1 个特殊字母
