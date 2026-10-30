# 题目：634. 寻找数组的错位排列（Find the Derangement of An Array）
# 思路：错排递推 f[i] = (i-1) * (f[i-1] + f[i-2])：数字 i 有 i-1 个非原位可放，放好后分「互换」与「不互换」两种情形。
# 时间复杂度：O(n)；空间复杂度：O(n)，保存全部 f 值。
class Solution:  # LeetCode 约定的题解类
    def findDerangement(self, n: int) -> int:  # n 是排列长度，返回错排方案数对 1e9+7 取模
        mod = 10**9 + 7  # 取模常量
        f = [1] + [0] * n  # f[0]=1 是边界（空排列 1 种），f[1]=0（长度 1 没有错排），其余先置 0
        for i in range(2, n + 1):  # 从长度 2 开始递推
            f[i] = (i - 1) * (f[i - 1] + f[i - 2]) % mod  # 错排递推：i 有 i-1 个非原位可放，放好后是 f[i-1] 或 f[i-2] 两种情形
        return f[n]  # 返回长度为 n 的错排方案数
