# 题目：2472. 不重叠回文子字符串的最大数目（Maximum Number of Non-overlapping Palindrome Substrings）
# 思路：区间 DP 预处理 g[i][j] 表示 s[i..j] 是否回文；再用 f[i] 表示后缀 s[i..] 中长度不小于 k 的不重叠回文子串最大个数，转移 f[i] = max(f[i+1], 1 + f[j+1])。
# 时间复杂度：O(n^2)，预处理与转移均为平方级；空间复杂度：O(n^2)，g 表占 n×n。
class Solution:  # LeetCode 约定的题解类
    def maxPalindromes(self, s: str, k: int) -> int:  # s 是原字符串，k 是可选取回文子串的最小长度
        n = len(s)  # 字符串长度，后续 DP 都依赖它
        g = [[True] * n for _ in range(n)]  # 二维布尔表 g[i][j]：子串 s[i..j] 是否回文，先全部置 True 以处理长度 ≤ 1 的区间
        for i in range(n - 1, -1, -1):  # 逆序枚举左端点，保证内部区间 g[i+1][j-1] 已算好
            for j in range(i + 1, n):  # 枚举右端点，长度 1 的区间无需再判
                g[i][j] = s[i] == s[j] and g[i + 1][j - 1]  # 两端相同且内部回文，则整体回文
        f = [0] * (n + 1)  # f[i]：从 i 开始的后缀可取到的最多不重叠回文个数，f[n] 作为哨兵 0
        for i in range(n - 1, -1, -1):  # 逆序推 f，保证 f[i+1] 与 f[j+1] 已就绪
            f[i] = f[i + 1]  # 不选以 i 开头的子串时，继承后一位的答案
            for j in range(i + k - 1, n):  # 枚举长度至少为 k 的右端点
                if g[i][j]:  # 只有回文区间才可以被选中
                    f[i] = max(f[i], 1 + f[j + 1])  # 选中一段得 1，之后从 j+1 继续，取最大值
        return f[0]  # 整串起点的最优值即答案
