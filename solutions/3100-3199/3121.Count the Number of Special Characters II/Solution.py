# 题目：3121. 统计特殊字母的数量 II（Count the Number of Special Characters II）
# 思路：用两个字典记录每个字符第一次与最后一次出现的下标；字母 c 特殊当且仅当小写 c 的最后一次出现在大写 C 的第一次之前。
# 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(1)，字典最多存 52 个键。
class Solution:  # LeetCode 约定的题解类
    def numberOfSpecialChars(self, word: str) -> int:  # word：输入字符串，返回满足条件的特殊字母个数
        first, last = {}, {}  # first/last：字符 → 第一次/最后一次出现的下标
        for i, c in enumerate(word):  # 同时取得下标与字符，顺序扫描一遍
            if c not in first:  # 这个字符是第一次出现
                first[c] = i  # 记录第一次出现的下标
            last[c] = i  # 每次出现都覆盖，循环结束后即为最后一次出现的下标
        return sum(  # 逐对枚举大小写字母，按布尔条件求和
            a in last and b in first and last[a] < first[b]  # 小写出现过、大写出现过，且小写最后一次出现在大写第一次之前
            for a, b in zip(ascii_lowercase, ascii_uppercase)  # 每个字母对产生一个 0/1 计数
        )  # sum 结束，作为函数返回值
