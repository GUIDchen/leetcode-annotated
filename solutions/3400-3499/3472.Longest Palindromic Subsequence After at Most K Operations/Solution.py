# 3472. Longest Palindromic Subsequence After at Most K Operations / 3472. 至多 K 次操作后的最长回文子序列
# 核心思路：区间记忆化搜索，枚举丢弃左端、丢弃右端或两端配对三种转移，配对代价为字母的环形距离。
# 复杂度：时间 O(n^2 * k)，空间 O(n^2 * k)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:  # 返回至多 k 次字符循环操作后的最长回文子序列长度
        @cache  # 用 cache 自动记忆化 (i, j, k) 状态
        def dfs(i: int, j: int, k: int) -> int:  # 求区间 [i, j] 在剩余 k 次操作下的最长回文子序列长度
            if i > j:  # 区间为空
                return 0  # 空区间长度为 0
            if i == j:  # 区间只剩一个字符
                return 1  # 单字符本身就是回文
            res = max(dfs(i + 1, j, k), dfs(i, j - 1, k))  # 丢弃左端或丢弃右端，取两者较大值
            d = abs(s[i] - s[j])  # 两字符在字母表上的直线距离
            t = min(d, 26 - d)  # 环形字母表上的最小距离，即配对所需的最少操作次数
            if t <= k:  # 剩余操作数足够让两端字符相同
                res = max(res, dfs(i + 1, j - 1, k - t) + 2)  # 两端配对成功，长度加 2 并扣掉本次代价
            return res  # 返回区间答案

        s = list(map(ord, s))  # 转成整数字码，便于直接相减求距离
        n = len(s)  # 字符个数
        ans = dfs(0, n - 1, k)  # 从整个字符串、k 次操作开始搜索
        dfs.cache_clear()  # 清理缓存，避免多组用例之间互相干扰
        return ans  # 返回最终答案
