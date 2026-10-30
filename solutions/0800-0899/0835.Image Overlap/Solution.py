# 题目：835. 图像重叠（Image Overlap）
# 思路：枚举 img1 与 img2 中所有为 1 的格子，用它们的坐标差作为平移向量，同一向量出现多少次就代表该平移下有多少个 1 重合，取最大值即可。
# 时间复杂度：O(n^4)，四重循环枚举两组 1 的所有配对；空间复杂度：O(n^2)，计数器最多记录 O(n^2) 个不同平移向量。
class Solution:  # LeetCode 约定的题解类
    def largestOverlap(self, img1: List[List[int]], img2: List[List[int]]) -> int:  # img1、img2 都是 n×n 的 0/1 矩阵，允许任意平移后求最多重合的 1 的个数
        n = len(img1)  # 图像边长
        cnt = Counter()  # 计数器：键为平移向量 (dx,dy)，值为该平移下重合的 1 的个数
        for i in range(n):  # 枚举 img1 的行
            for j in range(n):  # 枚举 img1 的列
                if img1[i][j]:  # 只有 img1 中为 1 的格子才可能贡献重叠
                    for h in range(n):  # 枚举 img2 的行
                        for k in range(n):  # 枚举 img2 的列
                            if img2[h][k]:  # 只有 img2 中为 1 的格子才能配对
                                cnt[(i - h, j - k)] += 1  # 同一个平移向量的重合计数加一
        return max(cnt.values()) if cnt else 0  # 取最大的重合次数；如果两图都没有 1，则答案为 0
