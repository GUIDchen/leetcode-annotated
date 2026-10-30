# 题目：1216. 验证回文串 III（Valid Palindrome III）
# 思路：区间 DP 求 s[i..j] 的最长回文子序列长度 f[i][j]，只要某区间满足 f[i][j]+k>=n，就说明删除不超过 k 个字符能变回文。
# 时间复杂度：O(n^2)，枚举所有区间；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def isValidPalindrome(self, s: str, k: int) -> bool:  # s：待判断的字符串；k：最多允许删除的字符数
        n = len(s)  # 字符串长度，后面 DP 的边界都要用到
        f = [[0] * n for _ in range(n)]  # 二维 DP 表：f[i][j] 表示 s[i..j] 的最长回文子序列长度；逐行新建可避免行之间共享同一引用
        for i in range(n):  # 初始化长度为 1 的区间
            f[i][i] = 1  # 单个字符本身就是回文，最长回文子序列长度是 1
        for i in range(n - 2, -1, -1):  # 左端点倒序枚举，保证用到 f[i+1][...] 时它已经算好
            for j in range(i + 1, n):  # 右端点正序枚举，只处理长度至少为 2 的区间
                if s[i] == s[j]:  # 两端字符相同，可以同时收进回文子序列的两头
                    f[i][j] = f[i + 1][j - 1] + 2  # 内部区间答案加上两端的这两个字符
                else:  # 两端字符不同，只能放弃其中一端
                    f[i][j] = max(f[i + 1][j], f[i][j - 1])  # 取放弃左端或放弃右端后的较大值
                if f[i][j] + k >= n:  # 长度 + 可删除数覆盖整个长度，等价于需要删除的字符数不超过 k
                    return True  # 条件满足，提前返回 True
        return False  # 所有区间都无法在 k 次删除内变成回文
