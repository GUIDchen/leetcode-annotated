# 题目：2947. 统计美丽子字符串 I（Count Beautiful Substrings I）
# 思路：枚举子串左右端点，边扩展右端点边累加元音个数，再用子串长度减去元音数得到辅音数；满足「元音数 == 辅音数且两者乘积能被 k 整除」就计数。
# 时间复杂度：O(n^2)，枚举所有子串；空间复杂度：O(1)，只用固定大小的元音集合和几个计数器。
class Solution:  # LeetCode 约定的题解类
    def beautifulSubstrings(self, s: str, k: int) -> int:  # s 为待统计的字符串，k 为整除参数，返回美丽子串的个数
        n = len(s)  # 字符串长度
        vs = set("aeiou")  # 元音字母集合，用于 O(1) 判断某个字符是不是元音
        ans = 0  # 记录美丽子串的个数
        for i in range(n):  # 枚举子串左端点 i
            vowels = 0  # 固定左端点后，重新累计当前子串中的元音数
            for j in range(i, n):  # 枚举子串右端点 j，子串为 s[i..j]
                vowels += s[j] in vs  # 布尔值可当 0/1 参与加法，这里累加当前子串的元音数
                consonants = j - i + 1 - vowels  # 子串长度减去元音数即为辅音数
                if vowels == consonants and vowels * consonants % k == 0:  # 元音数与辅音数相等，且两者乘积能被 k 整除
                    ans += 1  # 找到一个美丽子串，计数加一
        return ans  # 返回美丽子串总数
