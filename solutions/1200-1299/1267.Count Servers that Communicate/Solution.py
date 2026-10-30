# 题目：1267. 统计参与通信的服务器（Count Servers that Communicate）
# 思路：先统计每行、每列的服务器数量，再统计「本格有服务器且同行或同列服务器数大于 1」的格子数。
# 时间复杂度：O(mn)，两次遍历；空间复杂度：O(m+n)，行、列计数数组。
class Solution:  # LeetCode 约定的题解类
    def countServers(self, grid: List[List[int]]) -> int:  # grid 中 1 表示有服务器，0 表示空
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        row = [0] * m  # 记录每一行的服务器数量
        col = [0] * n  # 记录每一列的服务器数量
        for i in range(m):  # 逐行遍历
            for j in range(n):  # 逐列遍历
                row[i] += grid[i][j]  # 累加当前行的服务器数
                col[j] += grid[i][j]  # 累加当前列的服务器数
        return sum(  # 生成器求和：统计满足条件的服务器格数
            grid[i][j] and (row[i] > 1 or col[j] > 1)  # 本格有服务器（1 为真），且同行或同列还有第二台服务器，才能与别处通信
            for i in range(m)  # 遍历所有行
            for j in range(n)  # 遍历所有列
        )  # 结束 sum 的参数列表
