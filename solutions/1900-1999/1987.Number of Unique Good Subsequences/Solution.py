# 题目：1987. 不同的好子序列数目（Number of Unique Good Subsequences）
# 思路：按结尾字符去重计数：f 统计以 '1' 结尾的不同好子序列，g 统计以 '0' 结尾的，单独的 "0" 再另记一次。
# 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfUniqueGoodSubsequences(self, binary: str) -> int:  # 返回不同好子序列的数目（对 1e9+7 取模）
        f = g = 0  # f：以 '1' 结尾的数目；g：以 '0' 结尾的数目（暂不含单独的 "0"）
        ans = 0  # 单独的 "0" 是否存在的标记
        mod = 10**9 + 7  # 取模用的常数
        for c in binary:  # 从左到右扫每个字符
            if c == "0":  # 遇到 '0'
                g = (g + f) % mod  # 把 '0' 接在每个以 '1' 结尾的子序列后面，产生新的以 '0' 结尾的子序列
                ans = 1  # 单字符 "0" 也是好子序列
            else:  # 遇到 '1'
                f = (f + g + 1) % mod  # 把 '1' 接在所有已有子序列后面，再加上单独的 "1"
        ans = (ans + f + g) % mod  # 汇总三类计数后取模
        return ans  # 返回结果
