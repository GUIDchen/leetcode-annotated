# 题目：661. 图片平滑器（Image Smoother）
# 核心思路：对每个格子枚举 3x3 邻域，统计合法邻居的和与个数，用整除向下取整。
# 时间复杂度：O(m * n)；空间复杂度：O(m * n) 存结果。
class Solution:  # LeetCode 约定的题解类
    def imageSmoother(self, img: List[List[int]]) -> List[List[int]]:  # img 是 m 行 n 列的图像矩阵，返回同样尺寸的平滑结果
        m, n = len(img), len(img[0])  # 取出行数与列数
        ans = [[0] * n for _ in range(m)]  # 结果矩阵，初值全为 0
        for i in range(m):  # 遍历每一行
            for j in range(n):  # 遍历每一列
                s = cnt = 0  # s 累积邻域和，cnt 记录参与平均的格子数
                for x in range(i - 1, i + 2):  # 邻域行范围 [i-1, i+1]
                    for y in range(j - 1, j + 2):  # 邻域列范围 [j-1, j+1]
                        if 0 <= x < m and 0 <= y < n:  # 只统计落在矩阵内的邻居（边界格子邻居不足 9 个）
                            cnt += 1  # 合法邻居计数加一
                            s += img[x][y]  # 累加该邻居的值
                ans[i][j] = s // cnt  # 整除向下取整，符合题目要求
        return ans  # 返回平滑后的矩阵
