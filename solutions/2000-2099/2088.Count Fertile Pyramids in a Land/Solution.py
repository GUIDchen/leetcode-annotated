# 题目：2088. 统计农场中肥沃金字塔的数目（Count Fertile Pyramids in a Land）
# 思路：f[i][j] 表示以 (i,j) 为塔尖能形成的最大高度。正金字塔（塔尖朝上）自底向上递推，倒金字塔自顶向下递推，高度 h 的塔尖贡献 h 个金字塔。
# 时间复杂度：O(mn)，两轮二维遍历；空间复杂度：O(mn)，额外的 f 表。
class Solution:  # LeetCode 约定的题解类
    def countPyramids(self, grid: List[List[int]]) -> int:  # grid：0/1 矩阵，1 表示肥沃格子；返回金字塔总数
        m, n = len(grid), len(grid[0])  # 行数 m 与列数 n
        f = [[0] * n for _ in range(m)]  # 二维 dp 表，初始全 0：f[i][j] 为以 (i,j) 为塔尖的最大高度
        ans = 0  # 累计金字塔个数
        for i in range(m - 1, -1, -1):  # 第一轮自底向上：正金字塔的高度依赖下一行的三个相邻格
            for j in range(n):  # 从左到右遍历每一列
                if grid[i][j] == 0:  # 该格是空地，不能作为塔尖
                    f[i][j] = -1  # 用 -1 标记不可用，相邻格取 min 时会自然得到 0
                elif not (i == m - 1 or j == 0 or j == n - 1):  # 非边界格才可能形成高度 >= 1 的正金字塔（边界格保持初始值 0）
                    f[i][j] = min(f[i + 1][j - 1], f[i + 1][j], f[i + 1][j + 1]) + 1  # 高度取正下方三个相邻格中最小高度再加 1
                    ans += f[i][j]  # 高度为 h 的塔尖能形成高度 1..h 共 h 个正金字塔，全部累加
        for i in range(m):  # 第二轮自顶向下：统计倒金字塔（塔尖朝下，依赖上一行）
            for j in range(n):  # 从左到右遍历每一列
                if grid[i][j] == 0:  # 该格是空地，不能作为塔尖
                    f[i][j] = -1  # 同样用 -1 标记不可用格
                elif i == 0 or j == 0 or j == n - 1:  # 贴边界（第一行或左右边界）时无法向上扩展，落入本分支
                    f[i][j] = 0  # 高度显式置 0：单格不算金字塔，也不累加
                else:  # 非边界格才可能形成高度 >= 1 的倒金字塔
                    f[i][j] = min(f[i - 1][j - 1], f[i - 1][j], f[i - 1][j + 1]) + 1  # 高度取正上方三个相邻格中最小高度再加 1
                    ans += f[i][j]  # 高度为 h 的塔尖能形成高度 1..h 共 h 个倒金字塔，全部累加
        return ans  # 正金字塔与倒金字塔总数
