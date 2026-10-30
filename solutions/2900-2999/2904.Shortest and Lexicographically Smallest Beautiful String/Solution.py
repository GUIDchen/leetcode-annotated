# 题目：2904. 最短且字典序最小的美丽子字符串（Shortest and Lexicographically Smallest Beautiful String）
# 思路：枚举所有子串并统计其中 1 的个数，恰好为 k 时按「先比长度、再比字典序」的规则更新最优答案。
# 时间复杂度：O(n^3)，枚举 O(n^2) 个子串且每个统计 O(n)；空间复杂度：O(n)，用于暂存子串。
class Solution:  # LeetCode 约定的题解类
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:  # s：只含 0/1 的字符串；k：美丽子串中 1 的个数
        n = len(s)  # 字符串长度
        ans = ""  # 当前最优答案，空串表示还没找到
        for i in range(n):  # 枚举子串左端点 i
            for j in range(i + k, n + 1):  # 枚举右端点（不含）；长度至少为 k，否则不可能含 k 个 1
                t = s[i:j]  # 取出子串 s[i:j]
                if t.count("1") == k and (  # 1 的个数恰为 k 才美丽，才继续比较长度与字典序
                    not ans or j - i < len(ans) or (j - i == len(ans) and t < ans)  # 更短，或同长时字典序更小，才替换答案
                ):
                    ans = t  # 记录这个更优的子串
        return ans  # 没有美丽子串时返回空串，符合题目要求
