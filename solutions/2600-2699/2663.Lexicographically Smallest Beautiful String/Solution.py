# 题目：2663. 字典序最小的美丽字符串（Lexicographically Smallest Beautiful String）
# 核心思路：先把字符串转成字符列表，从右往左找第一个能增大的位置，把它换成最小的可行字母，再把右侧每一位都填成不与前两个字符相同的最小字母。
# 时间复杂度：O(n*k)，每位都在字母表内做常数级枚举；空间复杂度：O(n)，字符列表需要与字符串等长的额外空间。
class Solution:  # LeetCode 约定的题解类
    def smallestBeautifulString(self, s: str, k: int) -> str:  # s：原始字符串；k：可用字母表大小（前 k 个小写字母），返回字典序更大的最小美丽串
        n = len(s)  # 字符串长度
        cs = list(s)  # 转成字符列表，方便原地修改每一位
        for i in range(n - 1, -1, -1):  # 从右往左找第一个还能增大的位置 i
            p = ord(cs[i]) - ord('a') + 1  # p 是当前字符对应字母的下一个候选下标（'a' 记 0，所以加一）
            for j in range(p, k):  # 在字母表范围内，尝试把第 i 位换成更大的字母 j
                c = chr(ord('a') + j)  # 候选字符 c
                if (i > 0 and cs[i - 1] == c) or (i > 1 and cs[i - 2] == c):  # 美丽串不允许长度 ≥2 的回文：不能与前一个、前两个字符相同
                    continue  # 冲突就尝试下一个更大的字母
                cs[i] = c  # 确定第 i 位的字符（这是该位最小的可行值）
                for l in range(i + 1, n):  # 第 i 位右侧的每一格都要重新填成尽可能小的字符
                    for m in range(k):  # 在字母表内从小到大枚举候选字母 m
                        c = chr(ord('a') + m)  # 第 l 位的候选字符
                        if (l > 0 and cs[l - 1] == c) or (l > 1 and cs[l - 2] == c):  # 同样检查是否与前一个、前两个字符构成回文冲突
                            continue  # 冲突则继续尝试更大的字母
                        cs[l] = c  # 找到最小的可行字符，写到第 l 位
                        break  # 该位已填好，跳出内层枚举进入下一位
                return ''.join(cs)  # 越靠左的位置被增大字典序就越小，立即返回拼接后的字符串
        return ''  # 所有位置都无法增大，说明不存在更大的美丽串，返回空串
