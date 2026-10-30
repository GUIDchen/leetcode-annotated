# 题目：409. 最长回文串（Longest Palindrome）
# 思路：统计字符频次，每类字符取最大的偶数部分，若还有剩余字符就居中放一个使长度加 1。
# 时间复杂度：O(n)，一次统计加一次遍历频次；空间复杂度：O(字符集大小)，计数表所占空间。
class Solution:  # LeetCode 约定的题解类
    def longestPalindrome(self, s: str) -> int:  # s 由大小写字母组成，返回能拼出的最长回文串长度
        cnt = Counter(s)  # 统计每个字符的出现次数（Counter 由判题环境提供，无需 import）
        ans = sum(v // 2 * 2 for v in cnt.values())  # 每类字符取不超过频次的最大偶数，奇数频次多出的那一个先不用
        ans += int(ans < len(s))  # 若还有字符剩余就能居中放一个，长度加 1（int 把 bool 转成 0/1）
        return ans  # 返回最长回文串长度
