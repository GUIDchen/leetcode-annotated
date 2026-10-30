# 题目：2937. 使三个字符串相等（Make Three Strings Equal）
# 思路：共同前缀必须从下标 0 开始，先求出最长公共前缀长度 i，再把三个串都裁剪到长度 i。
# 时间复杂度：O(min(|s1|,|s2|,|s3|))，最多扫描最短串一遍；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findMinimumOperations(self, s1: str, s2: str, s3: str) -> int:  # s1、s2、s3：三个待比较的字符串；返回最少删除的字符总数
        s = len(s1) + len(s2) + len(s3)  # s：三个字符串的总长度，保留长度 i 的前缀后结果为 s - 3 * i
        n = min(len(s1), len(s2), len(s3))  # n：三者中的最短长度，公共前缀不可能超过它
        for i in range(n):  # 从下标 0 开始逐位比较
            if not s1[i] == s2[i] == s3[i]:  # 链式比较：任一位三个字符不全相同，公共前缀就断在这里
                return -1 if i == 0 else s - 3 * i  # i == 0 说明首位就不同，返回 -1；否则保留长度 i 的公共前缀
        return s - 3 * n  # 走完最短长度仍相同，说明最短串整体就是公共前缀
