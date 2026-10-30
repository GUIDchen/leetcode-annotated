# 题目：1163. 按字典序排在最后的子串（Last Substring in Lexicographical Order）
# 思路：双指针比较后缀，i 指向当前最优后缀起点、j 指向竞争者，k 记录已匹配长度，跳过被淘汰的起点。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def lastSubstring(self, s: str) -> str:  # 返回字典序最大的子串（即字典序最大的后缀）
        i, j, k = 0, 1, 0  # i 是候选最大后缀起点，j 是竞争者起点，k 是已匹配长度
        while j + k < len(s):  # 越界即结束比较
            if s[i + k] == s[j + k]:  # 当前位相同
                k += 1  # 继续比较下一位
            elif s[i + k] < s[j + k]:  # 竞争者更大
                i += k + 1  # i 跳过 i..i+k 这段不可能成为最大后缀的起点
                k = 0  # 重置匹配长度
                if i >= j:  # i 追上或超过 j
                    j = i + 1  # 保证 j 位于 i 之后
            else:  # 候选者更大
                j += k + 1  # j 跳过 j..j+k 这段被淘汰的起点
                k = 0  # 重置匹配长度
        return s[i:]  # 截取字典序最大的后缀
