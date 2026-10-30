# 题目：1416. 恢复数组（Restore The Array）
# 思路：dp[i] 表示后缀 s[i:] 的方案数，从右往左枚举第一段的右端点 j，把 dp[j+1] 累加进 dp[i]。
# 时间复杂度：O(n * log k)，每段长度受 k 限制；空间复杂度：O(n)，一维 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def numberOfArrays(self, s: str, k: int) -> int:  # s 是数字字符串，k 是每段上限，返回合法分割方案数
        mod = 10**9 + 7  # 方案数按题目要求对 1e9+7 取模
        n = len(s)  # 字符串长度
        f = [0] * (n + 1)  # f[i] 表示后缀 s[i:] 的合法分割方案数
        f[n] = 1  # 空后缀算一种方案，作为边界
        for i in range(n - 1, -1, -1):  # 从右往左递推
            if s[i] == '0':  # 以 0 开头不能单独成段（不能有前导零）
                continue  # 该位置无方案，跳过
            x = 0  # 当前段数值，逐位累加
            for j in range(i, n):  # 枚举当前段的右端点 j
                x = x * 10 + int(s[j])  # 把 s[j] 接到段尾，x 变成新段的数值
                if x > k:  # 段值超过 k 就不合法
                    break  # 再延长只会更大，直接跳出
                f[i] = (f[i] + f[j + 1]) % mod  # 累加剩余后缀的方案数
        return f[0]  # 整个字符串的方案数
