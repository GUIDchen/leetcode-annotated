# 题目：1043. 分隔数组以得到最大和（Partition Array for Maximum Sum）
# 思路：动态规划，f[i] 表示前 i 个元素划分后的最大和；枚举最后一段的起点 j，把它整体替换为段内最大值 mx 后与 f[j-1] 累加，取最优。
# 时间复杂度：O(nk)，每个位置枚举不超过 k 种段长；空间复杂度：O(n)，DP 数组。
class Solution:  # LeetCode 约定的题解类
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:  # arr 是原数组，k 是每段的最大长度，返回划分后的最大和
        n = len(arr)  # 数组元素个数 n
        f = [0] * (n + 1)  # DP 数组：f[i] 表示前 i 个元素划分后能得到的最大和，f[0] = 0 表示空前缀
        for i in range(1, n + 1):  # 从前 1 个元素开始递推到前 n 个
            mx = 0  # 最后一段的最大值，随着 j 左移逐步扩大
            for j in range(i, max(0, i - k), -1):  # j 是最后一段的起点（1 基），段长 i-j+1 不超过 k，故下界为 max(0, i-k)
                mx = max(mx, arr[j - 1])  # 把 arr[j-1] 纳入最后一段，更新段内最大值
                f[i] = max(f[i], f[j - 1] + mx * (i - j + 1))  # 取「沿用之前的划分」与「前 j-1 个的最优和 + 最后一段全变成 mx」中的较大者
        return f[n]  # 返回前 n 个元素划分后的最大和
