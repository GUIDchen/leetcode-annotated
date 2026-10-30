# 题目：2414. 最长的字母序连续子字符串的长度（Length of the Longest Alphabetical Continuous Substring）
# 思路：用 map(ord, s) 把字符映射成 ASCII 码，再用 pairwise 惰性取出相邻的两码；差为 1 则当前连续段加长，否则重置为 1，全程维护最大值。
# 时间复杂度：O(n)，字符串只遍历一次；空间复杂度：O(1)，只用常数个计数变量（pairwise 不产生额外列表）。
class Solution:  # LeetCode 约定的题解类
    def longestContinuousSubstring(self, s: str) -> int:  # s 是只含小写字母的字符串，返回最长字母序连续子串的长度
        ans = cnt = 1  # ans 记录最长长度；cnt 记录当前连续段长度，单个字符的长度为 1
        for x, y in pairwise(map(ord, s)):  # pairwise 依次给出相邻的两个 ASCII 码 (x, y)
            if y - x == 1:  # 两码相差 1，说明字母序连续
                cnt += 1  # 当前连续段长度加一
                ans = max(ans, cnt)  # 用当前长度刷新最大值
            else:  # 连续性中断
                cnt = 1  # 以当前字符为起点重新计数
        return ans  # 返回最长字母序连续子串的长度
