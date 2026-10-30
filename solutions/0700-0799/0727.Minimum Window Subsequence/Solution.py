# 题目：727. 最小窗口子序列（Minimum Window Subsequence）
# 思路：f[i][j] 表示 s1 前 i 个字符中、以第 i 个字符结尾且覆盖 s2 前 j 个字符的最短窗口起点；按行递推后枚举右端点取最短窗口。
# 时间复杂度：O(m·n)，双重枚举两串长度；空间复杂度：O(m·n)，DP 表大小为 (m+1)×(n+1)。
class Solution:  # LeetCode 约定的题解类
    def minWindow(self, s1: str, s2: str) -> str:  # s1 是主串，s2 是需要被完整包含的子序列
        m, n = len(s1), len(s2)  # m、n 分别是两串长度，作为 DP 的边界
        f = [[0] * (n + 1) for _ in range(m + 1)]  # 二维 DP 表，初值 0 表示该状态还无法匹配
        for i, a in enumerate(s1, 1):  # enumerate 第二个参数让下标从 1 开始，对应 DP 的 1-based 定义
            for j, b in enumerate(s2, 1):  # j 同样从 1 开始枚举 s2 前缀长度
                if a == b:  # 当前两字符相等，可以用 s1[i-1] 匹配 s2[j-1]
                    f[i][j] = i if j == 1 else f[i - 1][j - 1]  # j==1 时窗口只有当前字符，否则继承左上角记录的起点
                else:  # 字符不相等，当前字符无法参与匹配
                    f[i][j] = f[i - 1][j]  # 继承上一行同列的结果
        p, k = 0, m + 1  # p 记录最优左端点（0-based），k 记录最短长度，m+1 表示还没找到
        for i, a in enumerate(s1, 1):  # 枚举窗口右端点 i
            if a == s2[n - 1] and f[i][n]:  # 右端点字符必须是 s2 末字符，且 f[i][n] 非 0 表示 s2 完整出现过
                j = f[i][n] - 1  # 1-based 起点减 1 得到 0-based 下标
                if i - j < k:  # 更短的窗口才更新答案
                    k = i - j  # 更新最短长度
                    p = j  # 更新对应左端点
        return "" if k > m else s1[p : p + k]  # 没找到返回空串，否则切出 [p, p+k) 这段子串
