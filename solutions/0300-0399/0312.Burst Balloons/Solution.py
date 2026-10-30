# 题目：312. 戳气球（Burst Balloons）
# 思路：区间 DP。两端补虚拟气球 1，f[i][j] 表示只打爆开区间 (i,j) 内气球的最大金币，枚举最后被打爆的 k 划分左右子问题。
# 时间复杂度：O(n³)，三层枚举所有区间与分界点；空间复杂度：O(n²)，DP 二维表。
class Solution:  # LeetCode 约定的题解类
    def maxCoins(self, nums: List[int]) -> int:  # nums：每个气球上的数字
        n = len(nums)  # 气球个数
        arr = [1] + nums + [1]  # 两侧各补一个值为 1 的虚拟气球，省去边界判断
        f = [[0] * (n + 2) for _ in range(n + 2)]  # f[i][j]：只打爆开区间 (i,j) 内气球能得到的最大金币
        for i in range(n - 1, -1, -1):  # 从右往左枚举左端点，保证求 f[i][j] 时更窄的区间已经算好
            for j in range(i + 2, n + 2):  # 右端点至少比左端点大 2，开区间内才有气球
                for k in range(i + 1, j):  # 枚举区间内最后被打爆的气球 k
                    f[i][j] = max(f[i][j], f[i][k] + f[k][j] + arr[i] * arr[k] * arr[j])  # k 最后爆：左右子区间最优解相加，再加上 k 与边界 i、j 的乘积
        return f[0][-1]  # 答案是整个区间 (0, n+1) 的最大金币
