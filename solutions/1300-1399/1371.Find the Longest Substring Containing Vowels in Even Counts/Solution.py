# 题目：1371. 每个元音包含偶数次的最长子字符串（Find the Longest Substring Containing Vowels in Even Counts）
# 思路：用 5 位掩码记录 a、e、i、o、u 出现次数的奇偶性，只在某掩码第一次出现时记录位置，之后遇到相同掩码就用位置差更新答案。
# 时间复杂度：O(n)，字符串只扫一遍；空间复杂度：O(1)，掩码状态最多 32 种。
class Solution:  # LeetCode 约定的题解类
    def findTheLongestSubstring(self, s: str) -> int:  # s 为输入字符串，返回元音次数全为偶数的最长子串长度
        d = {0: -1}  # d 的键是 5 位奇偶掩码，值是它首次出现处字符的下标（-1 代表空前缀）
        ans = mask = 0  # ans 存答案；mask 是当前前缀里各元音出现次数的奇偶性
        for i, c in enumerate(s):  # 同时取出下标 i 与字符 c
            if c in "aeiou":  # 只有元音才需要更新掩码
                mask ^= 1 << (ord(c) - ord("a"))  # ord(c)-ord("a") 把元音映射到第 0 到第 4 位，异或即可翻转该位的奇偶性
            if mask in d:  # 该掩码此前出现过，说明这两个前缀之间每个元音都是偶数次
                j = d[mask]  # 取出该掩码首次出现的位置
                ans = max(ans, i - j)  # 用两个位置之差更新最长长度
            else:  # 该掩码第一次出现
                d[mask] = i  # 记下它的位置，供后续相同掩码计算长度
        return ans  # 返回最长长度（若整个串都不满足则 ans 为 0）
