# 题目：1092. 最短公共超序列（Shortest Common Supersequence）
# 思路：先求两串的最长公共子序列 DP 表 f，再从右下角回溯构造答案：字符相同则只写一次并同时消耗两串，否则沿 f 较大的方向取走一个字符；回溯结果是逆序，最后反转。
# 时间复杂度：O(m·n)，填表与回溯各一遍；空间复杂度：O(m·n)，f 表。
class Solution:  # LeetCode 约定的题解类
    def shortestCommonSupersequence(self, str1: str, str2: str) -> str:  # 返回同时包含 str1 与 str2 为子序列的最短字符串
        m, n = len(str1), len(str2)  # 两个串的长度
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j] 是 str1[:i] 与 str2[:j] 的 LCS 长度，多一行一列作为空串边界
        for i in range(1, m + 1):  # 枚举 str1 的前缀长度
            for j in range(1, n + 1):  # 枚举 str2 的前缀长度
                if str1[i - 1] == str2[j - 1]:  # 两个前缀的末尾字符相同，可以并入 LCS
                    f[i][j] = f[i - 1][j - 1] + 1  # 长度等于去掉这两个字符后的 LCS 再加一
                else:  # 末尾字符不同
                    f[i][j] = max(f[i - 1][j], f[i][j - 1])  # 取「丢掉 str1 末字符」与「丢掉 str2 末字符」中较大的 LCS
        ans = []  # 用来逆序收集答案字符
        i, j = m, n  # 从 DP 表右下角开始回溯
        while i or j:  # 还有字符没被消耗完
            if i == 0:  # str1 已用完
                j -= 1  # str2 指针左移
                ans.append(str2[j])  # 把 str2 剩余的字符接到答案里
            elif j == 0:  # str2 已用完
                i -= 1  # str1 指针左移
                ans.append(str1[i])  # 把 str1 剩余的字符接到答案里
            else:  # 两串都还有剩余字符
                if f[i][j] == f[i - 1][j]:  # 长度来自上方，说明 str1 的第 i 个字符不在 LCS 中
                    i -= 1  # str1 指针左移
                    ans.append(str1[i])  # 取走 str1 的这个字符
                elif f[i][j] == f[i][j - 1]:  # 长度来自左方，说明 str2 的第 j 个字符不在 LCS 中
                    j -= 1  # str2 指针左移
                    ans.append(str2[j])  # 取走 str2 的这个字符
                else:  # 上下都不等，说明这个字符是 LCS 里的公共字符
                    i, j = i - 1, j - 1  # 公共字符只需写一次，同时消耗两个串
                    ans.append(str1[i])  # 取走这个公共字符
        return ''.join(ans[::-1])  # 回溯得到的是逆序答案，反转后拼成字符串返回
