# 题目：2825. 循环增长使字符串子序列等于另一个字符串（Make String a Subsequence Using Cyclic Increments）
# 思路：贪心双指针，按顺序扫描 str1；每个字符可以原样使用，也可以循环加一，只要它能对上 str2 的下一个字符就立刻匹配。
# 时间复杂度：O(n)，n 为 str1 的长度；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def canMakeSubsequence(self, str1: str, str2: str) -> bool:  # str1：可以任选字符并各自循环加一的老字符串；str2：目标子序列；返回能否做到
        i = 0  # i 是 str2 中已经匹配上的前缀长度
        for c in str1:  # 顺序扫描 str1，保证选出的字符在子序列中仍保持原有的先后顺序
            d = "a" if c == "z" else chr(ord(c) + 1)  # 循环增长一位：'z' 加一后回到 'a'，其余字符用 chr(ord(c) + 1) 得到后继字母
            if i < len(str2) and str2[i] in (c, d):  # 还没匹配完且 str2[i] 等于当前字符的原形或增长形，就采用它
                i += 1  # 匹配成功，str2 的匹配位置前移一位
        return i == len(str2)  # 只有 str2 全部被匹配，才说明它可以是 str1 的子序列
