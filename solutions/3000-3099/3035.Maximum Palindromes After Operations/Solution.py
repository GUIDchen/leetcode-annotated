# 题目：3035. 回文字符串的最大数量（Maximum Palindromes After Operations）
# 思路：字符可自由交换，先统计总字符数与各字母出现次数的奇偶性，扣除必须留下的中位字符后，按单词长度升序贪心拼回文。
# 时间复杂度：O(L + k log k)，L 为字符总数、k 为单词数；空间复杂度：O(k)，排序与计数只需常数级额外空间。
class Solution:  # LeetCode 约定的题解类
    def maxPalindromesAfterOperations(self, words: List[str]) -> int:  # words 是允许任意交换字符的单词列表
        s = mask = 0  # s 统计字符总数；mask 的第 i 位记录字母 i 出现次数的奇偶性
        for w in words:  # 遍历所有单词
            s += len(w)  # 累加字符总数
            for c in w:  # 遍历单词中的每个字符
                mask ^= 1 << (ord(c) - ord("a"))  # 异或翻转该字母的奇偶位：奇数次则置位，偶数次则清零
        s -= mask.bit_count()  # 出现奇数次的字母各留一个做中位，剩余字符两两成对
        words.sort(key=len)  # 按长度升序排序，短单词更容易凑成回文
        ans = 0  # 记录能拼成的回文单词个数
        for w in words:  # 从短到长贪心地尝试每个单词
            s -= len(w) // 2 * 2  # 该单词消耗的字符数：偶数长度全用对子，奇数长度保留一个中位字符
            if s < 0:  # 可用字符已经不够
                break  # 更长的单词只会更不够，直接结束
            ans += 1  # 当前单词可以拼成回文，计数加一
        return ans  # 返回最多能拼成的回文单词数
