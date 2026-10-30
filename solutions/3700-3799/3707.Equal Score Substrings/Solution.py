# 题目：3707. Equal Score Substrings（3707. 相等子字符串分数）
# 核心思路：先把整串字母的 1~26 分数全部累加为右段，再从左往右把字符逐个搬进左段，途中任一步左右相等就说明存在合法切分。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def scoreBalance(self, s: str) -> bool:  # 判断能否把 s 切成两段非空子串且分数相等
        l = 0  # 左段分数
        r = sum(ord(c) - ord("a") + 1 for c in s)  # 先把整个串的分数累加进右段
        for c in s[:-1]:  # 枚举切分点：当前字符归左段，右段至少保留最后一个字符
            x = ord(c) - ord("a") + 1  # 把字母映射为 1~26 的分数
            l += x  # 把该字母记入左段
            r -= x  # 同时从右段扣掉
            if l == r:  # 两段分数相等，切分合法
                return True  # 返回存在
        return False  # 所有切分点都不满足
