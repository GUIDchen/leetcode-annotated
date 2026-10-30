# 题目：3122. 使矩阵满足条件的最少操作次数（Minimum Number of Operations to Satisfy Conditions）
# 思路：按列做动态规划，f[i][j] 表示第 i 列全部改成 j 时前 i 列的最少修改次数，转移时要求相邻两列取值不同。
# 时间复杂度：O(n * 10 * 10 + m * n)，n 为列数、m 为行数；空间复杂度：O(n * 10)。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, grid: List[List[int]]) -> int:  # 返回使矩阵任意相邻格子（上下、左右）取值都不同的最少修改次数
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数；下面按「列」为单位做动态规划
        f = [[inf] * 10 for _ in range(n)]  # f[i][j]：第 i 列最终全部改成 j 时，前 i 列的最小修改次数
        for i in range(n):  # 逐列递推
            cnt = [0] * 10  # cnt[x]：第 i 列中原始值为 x 的格子个数
            for j in range(m):  # 遍历第 i 列的每一行
                cnt[grid[j][i]] += 1  # 统计该列中各个数字出现的次数
            if i == 0:  # 第一列没有前一列的约束，单独初始化
                for j in range(10):  # 枚举第一列最终改成的数字 j
                    f[i][j] = m - cnt[j]  # 保留 cnt[j] 个原值，其余 m - cnt[j] 个都需要修改
            else:  # i > 0 时还必须保证与第 i-1 列的数字不同
                for j in range(10):  # 枚举本列最终的数字 j
                    for k in range(10):  # 枚举前一列最终的数字 k
                        if k != j:  # 只有 k != j 才允许转移，否则相邻格子仍相同
                            f[i][j] = min(f[i][j], f[i - 1][k] + m - cnt[j])  # 用「本列修改数 + 前一列最优值」更新最小值
        return min(f[-1])  # 最后一列取 10 种数字中的最小值即为答案
