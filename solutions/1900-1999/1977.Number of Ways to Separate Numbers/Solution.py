# 题目：1977. 划分数字的方案数（Number of Ways to Separate Numbers）
# 思路：先预处理 lcp 让两段数能 O(1) 比较大小，再用 dp[i][j]（前缀和形式）表示前缀 i 最后一段长度不超过 j 的方案数。
# 时间复杂度：O(n^2)；空间复杂度：O(n^2)，lcp 与 dp 两张表。
class Solution:  # LeetCode 约定的题解类
    def numberOfCombinations(self, num: str) -> int:  # num：只含数字的字符串，返回把它切成若干段非递减数字的方案数
        def cmp(i, j, k):  # 闭包：判断从 i、j 开始长度都为 k 的两段数，前者是否 >= 后者（用到后面才创建的 lcp）
            x = lcp[i][j]  # 两段数的公共前缀长度
            return x >= k or num[i + x] >= num[j + x]  # 前 k 位全相同则相等；否则比较第一个不同的字符就够了

        mod = 10**9 + 7  # 方案数要取模的模数
        n = len(num)  # 字符串长度
        lcp = [[0] * (n + 1) for _ in range(n + 1)]  # lcp[i][j]：后缀 num[i..] 与 num[j..] 的最长公共前缀长度
        for i in range(n - 1, -1, -1):  # i 从后往前推，保证 i+1 行的值已经算好
            for j in range(n - 1, -1, -1):  # j 同样从后往前推
                if num[i] == num[j]:  # 首字符相同才能继续比后面的字符
                    lcp[i][j] = 1 + lcp[i + 1][j + 1]  # 公共前缀长度等于右移一位的结果再加 1

        dp = [[0] * (n + 1) for _ in range(n + 1)]  # dp[i][j]：前缀 num[0..i) 切完、且最后一段长度不超过 j 的方案数（前缀和形式）
        dp[0][0] = 1  # 空前缀且最后一段长度为 0，作为基础方案数 1
        for i in range(1, n + 1):  # 枚举前缀长度 i
            for j in range(1, i + 1):  # 枚举最后一段的长度 j
                v = 0  # v：当上一段长度也恰好为 j 时新增的方案数
                if num[i - j] != '0':  # 最后一段不能有前导零，首字符非 '0' 才合法
                    if i - j - j >= 0 and cmp(i - j, i - j - j, j):  # 上一段也能取长度 j，且它的数值不大于当前段
                        v = dp[i - j][j]  # 这些方案全部合法
                    else:  # 否则上一段长度必须严格小于 j
                        v = dp[i - j][min(j - 1, i - j)]  # 用前缀和形式一次取到「长度不超过 min(j-1, i-j)」的全部方案
                dp[i][j] = (dp[i][j - 1] + v) % mod  # 前缀和递推：不超过 j 的方案 = 不超过 j-1 的方案 + 恰好为 j 的方案
        return dp[n][n]  # 整个串切完的方案总数
