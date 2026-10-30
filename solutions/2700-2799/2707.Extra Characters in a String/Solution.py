# 题目：2707. 字符串中的额外字符（Extra Characters in a String）
# 思路：动态规划，f[i] 表示前 i 个字符中最少剩下多少额外字符；第 i 个字符可单独作废，也可与某个起点 j 组成字典单词而不计代价。
# 时间复杂度：O(n^3)，两层枚举加切片比较，n 为串长；空间复杂度：O(n + D)，f 数组与字典集合，D 为字典总字符数。
class Solution:  # LeetCode 约定的题解类
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:  # s 是原串，dictionary 是可用的单词表
        ss = set(dictionary)  # 转成集合，后续 O(1) 判断子串是否在字典中
        n = len(s)  # 串长
        f = [0] * (n + 1)  # f[i] 表示前 i 个字符的最少额外字符数，先全部初始化为 0
        for i in range(1, n + 1):  # 按前缀长度从小到大递推
            f[i] = f[i - 1] + 1  # 最坏情况：第 i 个字符单独算作一个额外字符
            for j in range(i):  # 枚举单词起点 j
                if s[j:i] in ss and f[j] < f[i]:  # s[j:i] 是字典单词，且从更小的 f[j] 转移过来更优
                    f[i] = f[j]  # 用 f[j] 更新 f[i]，该段不产生额外字符
        return f[n]  # 整个串的最少额外字符数
