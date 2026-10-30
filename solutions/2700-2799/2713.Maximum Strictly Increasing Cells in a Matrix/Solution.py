# 题目：2713. 矩阵中严格递增的单元格数（Maximum Strictly Increasing Cells in a Matrix）
# 思路：按数值升序分组，dp[i][j] = 1 + max(rowMax[i], colMax[j])；同值格子先全部算完再统一更新行列最大值，保证严格递增。
# 时间复杂度：O(mn log(mn))，主要花在按键排序；空间复杂度：O(mn)，保存分组坐标。
class Solution:  # LeetCode 约定的题解类
    def maxIncreasingCells(self, mat: List[List[int]]) -> int:  # mat：m 行 n 列矩阵，返回最长严格递增路径的单元格数
        m, n = len(mat), len(mat[0])  # m 为行数，n 为列数
        g = defaultdict(list)  # 按数值分组：键是单元格值，值是坐标列表
        for i in range(m):  # 遍历每一行
            for j in range(n):  # 遍历每一列
                g[mat[i][j]].append((i, j))  # 把坐标 (i, j) 归入对应数值的分组
        rowMax = [0] * m  # rowMax[i]：第 i 行目前能接出的最长路径长度，初值为 0
        colMax = [0] * n  # colMax[j]：第 j 列目前能接出的最长路径长度，初值为 0
        ans = 0  # ans：全局最长长度
        for _, pos in sorted(g.items()):  # 按键值升序遍历分组，保证转移来源的值都更小
            mx = []  # 暂存本组每格的 dp 值，避免同值之间互相转移
            for i, j in pos:  # 第一轮：只按更小值留下的行列最大值计算 dp
                mx.append(1 + max(rowMax[i], colMax[j]))  # 从同行或同列最大值接过来，并把自己算作一格
                ans = max(ans, mx[-1])  # 用本组最新结果刷新全局答案
            for k, (i, j) in enumerate(pos):  # 第二轮：本组 dp 全部算完后才统一写回行列最大值
                rowMax[i] = max(rowMax[i], mx[k])  # 用本格 dp 更新所在行的最大值
                colMax[j] = max(colMax[j], mx[k])  # 用本格 dp 更新所在列的最大值
        return ans  # 返回最长严格递增路径的单元格数
