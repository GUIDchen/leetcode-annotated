# 题目：3216. 交换后字典序最小的字符串（Lexicographically Smallest String After a Swap）
# 思路：用 pairwise 枚举相邻两字符并取 ASCII 码，找到第一对「奇偶性相同且前大后小」的下标，交换一次后立即返回。
# 时间复杂度：O(n)，只扫一遍相邻字符对；空间复杂度：O(n)，pairwise 与字符串拼接都会产生与 n 同阶的临时对象。
class Solution:  # LeetCode 约定的题解类
    def getSmallestString(self, s: str) -> str:  # s 是允许交换一次的输入字符串
        for i, (a, b) in enumerate(pairwise(map(ord, s))):  # i 是左字符下标，(a, b) 是相邻两字符的 ASCII 码
            if (a + b) % 2 == 0 and a > b:  # a + b 为偶数说明两字符奇偶性相同；a > b 说明交换后字典序会变小
                return s[:i] + s[i + 1] + s[i] + s[i + 2 :]  # 交换第 i 与第 i+1 个字符，题目只允许交换一次，所以立刻返回
        return s  # 找不到可交换的相邻对，原字符串已经是字典序最小
