# 题目：1335. 工作计划的最低难度（Minimum Difficulty of a Job Schedule）
# 思路：区间划分型 DP。f[i][j] 表示前 i 个任务分成 j 天的最小总难度，倒序枚举最后一天的起点 k，用不断扩张的区间最大值做转移。
# 时间复杂度：O(n^2 * d)；空间复杂度：O(n * d)，即 DP 表大小。
class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:  # jobDifficulty 为任务难度（顺序固定），d 为计划天数
        n = len(jobDifficulty)  # 任务数量
        f = [[inf] * (d + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个任务分成 j 天的最小总难度，先全部设为无穷大
        f[0][0] = 0  # 边界：0 个任务 0 天，总难度为 0
        for i in range(1, n + 1):  # 枚举任务前缀长度 i
            for j in range(1, min(d + 1, i + 1)):  # 枚举天数 j，最多 min(d, i) 天（每天至少一个任务）
                mx = 0  # 最后一天任务区间的最大难度
                for k in range(i, 0, -1):  # 倒序枚举最后一天的起点 k，使区间最大值可以增量维护
                    mx = max(mx, jobDifficulty[k - 1])  # 把第 k 个任务并入区间并更新最大值
                    f[i][j] = min(f[i][j], f[k - 1][j - 1] + mx)  # 转移：前 k-1 个任务分 j-1 天 + 最后一天的最大难度
        return -1 if f[n][d] >= inf else f[n][d]  # 无解（如天数多于任务数）返回 -1
