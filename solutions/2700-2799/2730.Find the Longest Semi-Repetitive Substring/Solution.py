# 题目：2730. 找到最长的半重复子字符串（Find the Longest Semi-Repetitive Substring）
# 思路：滑动窗口 [j, i]，cnt 记录窗口内相邻相等对的数量，超过 1 就右移左端点收缩。
# 时间复杂度：O(n)，左右指针各只前进一次；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def longestSemiRepetitiveSubstring(self, s: str) -> int:  # 返回最长的半重复子串长度
        ans, n = 1, len(s)  # ans 记录最长长度（单字符也满足），n 为字符串长度
        cnt = j = 0  # cnt 是窗口内相邻相等对的数量，j 是窗口左端点
        for i in range(1, n):  # 右端点 i 从 1 开始，逐步向右扩张窗口
            cnt += s[i] == s[i - 1]  # 新加入的 s[i] 若与左邻相等，就多一个相邻相等对
            while cnt > 1:  # 相等对超过 1 个就不满足半重复，需要收缩左端点
                cnt -= s[j] == s[j + 1]  # 移出 s[j] 时，若它与 s[j+1] 相等，则减少一个相等对
                j += 1  # 左端点右移一位
            ans = max(ans, i - j + 1)  # 用当前窗口长度更新答案
        return ans  # 返回最长半重复子串长度
