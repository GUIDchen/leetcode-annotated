# 题目：2311. 小于等于 K 的最长二进制子序列（Longest Binary Subsequence Less Than or Equal to K）
# 思路：从低位向高位贪心扩展，末尾的 0 一定保留；1 只有在当前数值加上该位权重后仍不超过 k 时才保留。
# 时间复杂度：O(n)，n 为字符串长度，只遍历一遍；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def longestSubsequence(self, s: str, k: int) -> int:  # s 是二进制字符串，k 是上界
        ans = v = 0  # ans 是当前子序列长度，v 是它对应的数值
        for c in s[::-1]:  # 反转字符串，从最低位开始处理
            if c == "0":  # 0 放在最低位不改变数值，总是可以保留
                ans += 1  # 保留这个 0，长度加一
            elif ans < 30 and (v | 1 << ans) <= k:  # 1 需位数安全（ans < 30）且加入后数值不超过 k 才保留
                v |= 1 << ans  # 把这一位的权重并入当前数值
                ans += 1  # 成功保留一个 1，长度加一
        return ans  # 返回最长子序列长度
