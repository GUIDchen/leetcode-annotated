# 题目：741. 摘樱桃（Cherry Pickup）
# 思路：一来一回等价于「两个人同时从 (0,0) 走到 (n-1,n-1)」，用 k = i + j 作为阶段，f[k][i1][i2] 表示两人分别在第 i1、i2 行时的最大樱桃数。
# 时间复杂度：O(n^3)，状态数与转移都是 O(n^3)；空间复杂度：O(n^3)，三维 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def cherryPickup(self, grid: List[List[int]]) -> int:  # grid：n×n 地图，1 有樱桃、0 为空、-1 为障碍
        n = len(grid)  # 地图边长
        f = [[[-inf] * n for _ in range(n)] for _ in range((n << 1) - 1)]  # 三维 DP：f[k][i1][i2]，用 -inf 表示状态不可达
        f[0][0][0] = grid[0][0]  # 起点唯一状态：两人都在 (0,0)，樱桃只算一次
        for k in range(1, (n << 1) - 1):  # 枚举步数 k = 行 + 列，范围 1 .. 2n-2
            for i1 in range(n):  # 枚举第一个人的行号
                for i2 in range(n):  # 枚举第二个人的行号
                    j1, j2 = k - i1, k - i2  # 由步数与行反推出两人的列号
                    if (  # 下面判断该状态是否合法：
                        not 0 <= j1 < n  # 第一个人的列越界
                        or not 0 <= j2 < n  # 第二个人的列越界
                        or grid[i1][j1] == -1  # 第一个人踩到障碍
                        or grid[i2][j2] == -1  # 第二个人踩到障碍
                    ):  # 结束条件
                        continue  # 非法状态直接跳过
                    t = grid[i1][j1]  # 当前位置的樱桃
                    if i1 != i2:  # 两人不在同一格才加上第二个人的樱桃，重合只算一次
                        t += grid[i2][j2]  # 加上第二个人所在格的樱桃
                    for x1 in range(i1 - 1, i1 + 1):  # 枚举第一个人上一阶段的行号（只能从上方或左侧走来）
                        for x2 in range(i2 - 1, i2 + 1):  # 枚举第二个人上一阶段的行号
                            if x1 >= 0 and x2 >= 0:  # 两行号都合法才可转移
                                f[k][i1][i2] = max(f[k][i1][i2], f[k - 1][x1][x2] + t)  # 用上一阶段的最优值加上本格樱桃更新当前状态
        return max(0, f[-1][-1][-1])  # 终点共处一格；与 0 取大表示无解时返回 0
