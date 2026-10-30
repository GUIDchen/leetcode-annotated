# 题目：629. K 个逆序对数组（K Inverse Pairs Array）
# 思路：f[j] 表示当前长度下恰好 j 个逆序对的方案数；插入新元素只会新增 0..i-1 个逆序对，于是转移是窗口求和，用前缀和 s 优化成 O(1)。
# 时间复杂度：O(n * k)，两层递推；空间复杂度：O(k)，只保留一维 f 与前缀和 s。
class Solution:  # LeetCode 约定的题解类
    def kInversePairs(self, n: int, k: int) -> int:  # n 是排列长度，k 是逆序对个数，返回方案数对 1e9+7 取模
        mod = 10**9 + 7  # 取模常量
        f = [1] + [0] * k  # f[0]=1 是边界，f[1..k] 先置 0；f[j] 表示恰好 j 个逆序对的方案数
        s = [0] * (k + 2)  # 前缀和数组 s，多开一位避免 s[k+1] 越界
        for i in range(1, n + 1):  # 依次计算长度为 1 到 n 的排列
            for j in range(1, k + 1):  # 逐个计算恰好 j 个逆序对的方案数（j=0 恒为 1，跳过）
                f[j] = (s[j + 1] - s[max(0, j - (i - 1))]) % mod  # 窗口和：s[j+1] - s[max(0, j-(i-1))]；Python 的 % 自动返回非负数，无需补偿
            for j in range(1, k + 2):  # 用刚算好的 f 重建前缀和，供下一轮 i 使用
                s[j] = (s[j - 1] + f[j - 1]) % mod  # 前缀和递推：s[j] = s[j-1] + f[j-1]
        return f[k]  # 返回长度为 n 且恰好 k 个逆序对的方案数
