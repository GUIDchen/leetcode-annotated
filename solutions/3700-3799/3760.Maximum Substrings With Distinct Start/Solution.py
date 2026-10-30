# 3760. 不同首字母的子字符串数目（Maximum Substrings With Distinct Start）
# 核心思路：每个不同的字符都能作为某个子串的首字母，因此最多可选的不同首字母子串数就等于字符串中不同字符的种数。
# 复杂度：时间 O(n)，空间 O(1)（固定 26 个桶）。
class Solution:  # 定义解法类
    def maxDistinct(self, s: str) -> int:  # 接口：返回首字母互不相同的子串最大数量
        return len(set(s))  # 不同字符的种数即答案：每种首字母最多贡献一个子串
