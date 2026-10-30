# 题目：2450. 应用操作后不同二进制字符串的数量（Number of Distinct Binary Strings After Applying Operations）
# 思路：长度为 k 的窗口共有 n-k+1 个，每个窗口翻转与否相互独立，所以不同字符串数量为 2^(n-k+1)。
# 时间复杂度：O(n)（快速幂的乘法次数与指数位数同阶，n 为串长）；空间复杂度：O(1)，只存常量。
class Solution:  # LeetCode 约定的题解类
    def countDistinctStrings(self, s: str, k: int) -> int:  # s：原二进制字符串；k：每次操作选取的子串长度
        return pow(2, len(s) - k + 1) % (10**9 + 7)  # 独立窗口数为 n-k+1，方案数即 2 的该次方，再对 10^9+7 取模
