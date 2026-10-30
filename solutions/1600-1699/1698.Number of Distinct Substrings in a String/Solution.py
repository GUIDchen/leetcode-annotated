# 题目：1698. 字符串的不同子字符串个数（Number of Distinct Substrings in a String）
# 思路：用集合推导式枚举所有 O(n^2) 个子串，切片后交给 set 自动去重，最后取集合大小。
# 时间复杂度：O(n^3)，枚举 n^2 个子串、每次切片与哈希是 O(n)；空间复杂度：O(n^3) 个字符量级，最坏所有子串都不同。
class Solution:  # LeetCode 约定的题解类
    def countDistinct(self, s: str) -> int:  # s：待统计的输入字符串
        n = len(s)  # 字符串长度
        return len({s[i:j] for i in range(n) for j in range(i + 1, n + 1)})  # 双重循环枚举所有子串并去重，返回不同子串个数
