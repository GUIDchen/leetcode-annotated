# 题目：14. 最长公共前缀（Longest Common Prefix）
# 思路：以第一个串为基准逐列比较，其余任一串在该列不同或长度不足，就返回基准串的前 i 个字符。
# 时间复杂度：O(n·L)，n 是字符串个数、L 是公共前缀长度；空间复杂度：O(1)，只返回前缀切片。
class Solution:  # LeetCode 约定的题解类
    def longestCommonPrefix(self, strs: List[str]) -> str:  # strs 是字符串数组
        for i in range(len(strs[0])):  # 逐列遍历基准串（第 0 个串）的下标
            for s in strs[1:]:  # 拿其余每个字符串比较这一列
                if len(s) <= i or s[i] != strs[0][i]:  # 该串长度不够，或该位字符不同
                    return s[:i]  # 前 i 个字符即最长公共前缀（此时 s[:i] 与 strs[0][:i] 相同）
        return strs[0]  # 所有列都相同，基准串整体就是最长公共前缀
