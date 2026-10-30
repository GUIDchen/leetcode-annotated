# 题目：3713. 最长的平衡子串 I（Longest Balanced Substring I）
# 思路：枚举左端点并向右扩展，用 Counter 统计各字符出现次数；当「最大出现次数 × 不同字符个数 == 子串长度」时每种字符次数都等于最大值，子串平衡，据此更新最长长度。
# 时间复杂度：O(n²)，每个左端点扫一遍后缀；空间复杂度：O(1)，最多 26 个字母的计数。
class Solution:  # LeetCode 约定的题解类
    def longestBalanced(self, s: str) -> int:  # s：只含小写字母的字符串；返回最长平衡子串的长度
        n = len(s)  # 字符串长度
        ans = 0  # 记录最长平衡子串长度
        for i in range(n):  # 枚举子串左端点
            cnt = Counter()  # 当前子串中各字符的出现次数
            mx = v = 0  # mx：当前子串的最大出现次数；v：不同字符个数
            for j in range(i, n):  # 枚举子串右端点
                cnt[s[j]] += 1  # 当前字符计数加一
                mx = max(mx, cnt[s[j]])  # 更新最大出现次数
                if cnt[s[j]] == 1:  # 该字符在子串中首次出现
                    v += 1  # 不同字符个数加一
                if mx * v == j - i + 1:  # 最大次数 × 字符种类数 == 子串长度，说明每种字符次数都等于 mx
                    ans = max(ans, j - i + 1)  # 更新答案
        return ans  # 返回最长平衡子串长度
