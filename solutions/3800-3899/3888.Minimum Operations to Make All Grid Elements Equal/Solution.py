# 题目：3888. 使所有网格元素相等的最小操作次数（Minimum Operations to Make All Grid Elements Equal）
# 思路：每次把 k×k 子矩阵整体加 1，数值只能增大，故最终目标值只能是最大值或最大值+1；对固定目标值从左上到右下贪心补齐，用二维差分数组 O(1) 完成整块加一。
# 时间复杂度：O(m × n)，只需两次可行性检查；空间复杂度：O(m × n)，存放二维差分数组。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, grid: list[list[int]], k: int) -> int:  # grid：m×n 网格；k：每次操作所选子矩阵的边长
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        mx = max(max(row) for row in grid)  # 网格中的最大值，作为目标值的下界

        def check(target: int) -> int:  # 内部函数 check(target)：判断能否全变成 target，可行则返回总操作次数
            diff = [[0] * (n + 2) for _ in range(m + 2)]  # 二维差分数组，多开两行两列以省去边界判断
            total_ops = 0  # 累计操作次数

            for i, row in enumerate(grid, 1):  # 按行遍历，enumerate 起点取 1 让差分下标与网格错开一位
                for j, val in enumerate(row, 1):  # 按列遍历，j 同样是差分下标
                    diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1]  # 二维前缀和还原，得到当前格子此前被覆盖的次数

                    cur_val = val + diff[i][j]  # 当前格子的真实值 = 原值 + 之前所有操作的增量

                    if cur_val > target:  # 只能增加，已经超过 target 就不可能再拉平
                        return -1  # 该目标值不可行

                    if cur_val < target:  # 当前值偏小，需要继续补齐
                        if i + k - 1 > m or j + k - 1 > n:  # 以 (i, j) 为左上角的 k×k 子矩阵必须完整落在网格内
                            return -1  # 子矩阵越界，无法补齐这个格子

                        needed = target - cur_val  # 需要补足的差值
                        total_ops += needed  # 每补 1 算一次操作
                        diff[i][j] += needed  # 差分数组单点加，表示从这里开始被覆盖 needed 次
                        diff[i + k][j] -= needed  # 第 i+k 行减去 needed，撤销对下方的影响
                        diff[i][j + k] -= needed  # 第 j+k 列减去 needed，撤销对右方的影响
                        diff[i + k][j + k] += needed  # 右下角补回 needed，抵消上面两次减法（容斥）
            return total_ops  # 全部格子都等于 target，返回总操作次数

        for t in range(mx, mx + 2):  # 目标值只需尝试最大值与最大值+1
            res = check(t)  # 计算该目标值下的最少操作次数，-1 表示不可行
            if res != -1:  # 找到可行方案
                return res  # 返回该最少操作次数

        return -1  # 两种目标值都不可行
