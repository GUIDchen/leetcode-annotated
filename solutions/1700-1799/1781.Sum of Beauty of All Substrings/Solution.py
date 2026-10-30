# 题目：1781. 所有子字符串美丽值之和（Sum of Beauty of All Substrings）
# 思路：枚举子串左端点 i，右端点 j 向右扩展时增量维护字母频次，每步用计数器的最值之差累加美丽值。
# 时间复杂度：O(n^2 * 26)，双重枚举子串并求计数最值；空间复杂度：O(26)，即常数空间。
class Solution:  # LeetCode 约定的题解类
    def beautySum(self, s: str) -> int:  # s 是只含小写字母的字符串
        ans, n = 0, len(s)  # ans 累加所有子串的美丽值，n 是字符串长度
        for i in range(n):  # 枚举子串左端点
            cnt = Counter()  # 当前子串的字母频次表，换左端点就重新开一个
            for j in range(i, n):  # 右端点从 i 开始向右扩展
                cnt[s[j]] += 1  # 把新字符计入当前子串
                ans += max(cnt.values()) - min(cnt.values())  # 出现过的字母中最大频次减最小频次即美丽值
        return ans  # 返回所有子串的美丽值之和
