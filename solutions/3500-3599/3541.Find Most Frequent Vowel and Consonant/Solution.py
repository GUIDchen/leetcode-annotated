# 题目：3541. 找到频率最高的元音和辅音（Find Most Frequent Vowel and Consonant）
# 思路：用 Counter 统计每个字母的出现次数，分别求出元音与辅音的最大频率，相加即为答案。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(26)，即 O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxFreqSum(self, s: str) -> int:  # s：只含小写字母的输入字符串
        cnt = Counter(s)  # 哈希计数：键为字符，值为该字符出现的次数
        a = b = 0  # a 记录最高元音频率，b 记录最高辅音频率
        for c, v in cnt.items():  # 遍历每个出现过的字符及其次数
            if c in "aeiou":  # 判断该字符是否为五个元音之一
                a = max(a, v)  # 是元音，用它去更新最高元音频率
            else:  # 否则当作辅音处理
                b = max(b, v)  # 用它去更新最高辅音频率
        return a + b  # 返回最高元音频率与最高辅音频率之和
