# 题目：1763. 最长的美好子字符串（Longest Nice Substring）
# 思路：枚举所有子串，用集合记录出现过的字符，用 all 检查每个字符的大写与小写形式是否都在集合中，取最长者。
# 时间复杂度：O(n^3)，枚举 O(n^2) 个子串且每次 O(n) 检查；空间复杂度：O(n)，集合最多存 52 个字符。
class Solution:  # LeetCode 约定的题解类
    def longestNiceSubstring(self, s: str) -> str:  # s：由大小写字母组成的字符串
        n = len(s)  # 字符串长度
        ans = ''  # 当前找到的最长美好子串，初值为空串
        for i in range(n):  # 枚举子串起点
            ss = set()  # 记录子串 s[i..j] 中出现过的字符
            for j in range(i, n):  # 枚举子串终点，逐步扩展右端
                ss.add(s[j])  # 把新字符加入集合
                if (  # 下面两个条件同时成立才更新答案
                    all(c.lower() in ss and c.upper() in ss for c in ss)  # 每个字符的大写和小写形式都出现在集合中
                    and len(ans) < j - i + 1  # 并且当前子串比已记录的答案更长
                ):
                    ans = s[i : j + 1]  # 记录当前子串为新的最优解
        return ans  # 返回最长美好子串，没有则返回空串
