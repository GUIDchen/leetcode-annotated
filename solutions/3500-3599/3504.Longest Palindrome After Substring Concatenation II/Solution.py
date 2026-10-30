# 题目：3504. 子字符串连接后的最长回文串 II（Longest Palindrome After Substring Concatenation II）
# 思路：先中心扩展求出 s、t 各自每个起点的最长回文长度；再把 t 反转，用 f[i][j] 求 s 前缀与反转 t 前缀的匹配长度，匹配段左右对称成回文，两侧各可再接一段原串中的回文。
# 时间复杂度：O(n² + m·n)；空间复杂度：O(m·n)，主要开销是二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def longestPalindrome(self, s: str, t: str) -> int:  # s、t：两个待拼接的字符串，返回拼接后可能的最长回文长度
        def expand(s: str, g: List[int], l: int, r: int):  # 从中心 (l, r) 向两侧扩展，更新以 l 为起点的最长回文长度
            while l >= 0 and r < len(s) and s[l] == s[r]:  # 两侧字符相等就继续向外扩
                g[l] = max(g[l], r - l + 1)  # 当前回文的起点是 l，长度为 r - l + 1
                l, r = l - 1, r + 1  # 左端点左移一位、右端点右移一位

        def calc(s: str) -> List[int]:  # 预处理：算出字符串中每个起点的最长回文长度
            n = len(s)  # 当前串长度
            g = [0] * n  # 结果数组，先全部置 0
            for i in range(n):  # 枚举每个可能的回文中心
                expand(s, g, i, i)  # 奇数长度回文，中心是单个字符
                expand(s, g, i, i + 1)  # 偶数长度回文，中心在两个字符之间
            return g  # 返回每个起点的最长回文长度

        m, n = len(s), len(t)  # 记录两个串的长度
        t = t[::-1]  # 反转 t：此后 s 的某段与 t 的某段相等，正好对应原题意里 s 与 t 首尾对称的一段
        g1, g2 = calc(s), calc(t)  # g1[i]/g2[j]：以 i/j 为起点、向右延伸的最长回文长度
        ans = max(*g1, *g2)  # 答案至少可以完全取自 s，或完全取自 t
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：s 前 i 个字符与 t 前 j 个字符的匹配长度
        for i, a in enumerate(s, 1):  # i 表示 s 的前缀长度，a 即 s[i-1]
            for j, b in enumerate(t, 1):  # j 表示 t 的前缀长度，b 即 t[j-1]
                if a == b:  # 末尾字符相同，才可能继续向外匹配
                    f[i][j] = f[i - 1][j - 1] + 1  # 匹配长度在去掉末尾字符的方案上加一
                    ans = max(ans, f[i][j] * 2 + (0 if i >= m else g1[i]))  # 匹配段左右对称共 2f 个字符，再接上 s 里从 i 开始的一段回文
                    ans = max(ans, f[i][j] * 2 + (0 if j >= n else g2[j]))  # 或者接上 t 里从 j 开始的一段回文
        return ans  # 返回最长回文的长度
