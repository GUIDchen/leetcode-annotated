# 题目：1478. 安排邮筒（Allocate Mailboxes）
# 思路：排序后做区间 DP。g[i][j] 表示只用 1 个邮筒服务 houses[i..j] 的最小距离和（邮筒放在中位数处）；f[i][j] 表示前 i+1 个房子放 j 个邮筒的最小代价，枚举最后一个邮筒覆盖的起始位置 p 转移。
# 时间复杂度：O(n^2 * k)（区间预处理 O(n^2)）；空间复杂度：O(n^2 + n*k)。
class Solution:  # LeetCode 约定的题解类
    def minDistance(self, houses: List[int], k: int) -> int:  # houses：房子坐标；k：邮筒个数
        houses.sort()  # 排序后距离具有单调性，中位数位置才是最优放法
        n = len(houses)  # 房子个数
        g = [[0] * n for _ in range(n)]  # g[i][j]：用 1 个邮筒服务第 i..j 个房子的最小距离和
        for i in range(n - 2, -1, -1):  # i 从后往前枚举区间左端
            for j in range(i + 1, n):  # j 枚举区间右端，保证 i < j
                g[i][j] = g[i + 1][j - 1] + houses[j] - houses[i]  # 两端各剥一个房子，最外层房子的距离贡献为 houses[j] - houses[i]
        f = [[inf] * (k + 1) for _ in range(n)]  # f[i][j]：前 i+1 个房子安排 j 个邮筒的最小总距离
        for i in range(n):  # 依次扩展已处理的房子数量
            f[i][1] = g[0][i]  # 只放 1 个邮筒时，全部房子都由它服务
            for j in range(2, min(k + 1, i + 2)):  # 枚举邮筒数量 j，满足 2 <= j <= k 且 j <= i+1
                for p in range(i):  # 枚举最后一个邮筒服务的起始房子 p+1，前 p+1 个房子用 j-1 个邮筒
                    f[i][j] = min(f[i][j], f[p][j - 1] + g[p + 1][i])  # 前半段最优 + 最后一段单邮筒代价
        return f[-1][k]  # 全部 n 个房子安排 k 个邮筒的最小总距离
