# 题目：3042. 统计前后缀下标对 I（Count Prefix and Suffix Pairs I）
# 核心思路：枚举每个下标 i 与其后的 j，直接用 startswith / endswith 判断 words[i] 是否同时是 words[j] 的前缀和后缀。
# 时间复杂度：O(n^2 * L)，每次判断要扫描字符串长度 L；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def countPrefixSuffixPairs(self, words: List[str]) -> int:  # words：待统计的字符串数组，返回同时满足前缀与后缀关系的下标对数目
        ans = 0  # ans：累计满足条件的下标对数量
        for i, s in enumerate(words):  # enumerate 同时拿到下标 i 和候选串 s，i 之前的下标不必作为左端点
            for t in words[i + 1 :]:  # 只遍历 i 之后的字符串 t，避免重复统计同一个下标对
                ans += t.endswith(s) and t.startswith(s)  # endswith 判后缀、startswith 判前缀；两个布尔值相加为 1 或 0，直接累加到答案
        return ans  # 返回统计到的下标对总数
