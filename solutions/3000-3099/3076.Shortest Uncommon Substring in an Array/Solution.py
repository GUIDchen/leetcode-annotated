# 题目：3076. 数组中的最短非公共子字符串（Shortest Uncommon Substring in an Array）
# 思路：对每个字符串按子串长度从小到大、同长度按字典序枚举全部子串，逐个检查它是否出现在别的字符串中，第一个合法的就是答案。
# 时间复杂度：O(n^2 * L^3)，n 为字符串个数、L 为最大长度（枚举子串并对每个子串做包含判断）；空间复杂度：O(n * L)，答案数组。
class Solution:  # LeetCode 约定的题解类
    def shortestSubstrings(self, arr: List[str]) -> List[str]:  # arr：输入的非空字符串数组；返回每个位置的最短非公共子字符串
        ans = [""] * len(arr)  # 答案数组，默认空串表示该位置不存在合法子串
        for i, s in enumerate(arr):  # 逐个字符串独立求解，i 是下标、s 是当前字符串
            m = len(s)  # 当前字符串长度
            for j in range(1, m + 1):  # 按子串长度 j 从小到大枚举，保证先找到的答案是最短的
                for l in range(m - j + 1):  # 枚举长度为 j 的子串的起始下标 l
                    sub = s[l : l + j]  # 取出当前要检验的子串
                    if not ans[i] or ans[i] > sub:  # 答案为空，或者新子串字典序更小（同长度时取字典序最小），才值得替换
                        if all(k == i or sub not in t for k, t in enumerate(arr)):  # all 短路求值：只要该子串没出现在其它任一字符串中，就说明它合法
                            ans[i] = sub  # 记录为当前最优答案
                if ans[i]:  # 当前长度已找到答案，更长的子串不可能更短，直接结束长度枚举
                    break  # 跳出长度枚举，进入下一个字符串
        return ans  # 返回全部字符串的答案
