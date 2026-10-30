# 3898. 统计每个顶点的度 / Find the Degree of Each Vertex
# 核心思路：无向图以邻接矩阵给出，逐行求和即得到每个顶点连出的边数，也就是该顶点的度。
# 复杂度：时间 O(n^2)，空间 O(1)（不计返回数组）。
class Solution:  # 题解类
    def findDegrees(self, matrix: list[list[int]]) -> list[int]:  # matrix 为邻接矩阵，返回每个顶点的度
        ans = [0] * len(matrix)  # 存放各顶点的度，初值为 0
        for i, row in enumerate(matrix):  # 逐行（逐个顶点）统计
            for x in row:  # 遍历该顶点的整行
                ans[i] += x  # 累加该行元素即得到度数
        return ans  # 返回每个顶点的度
