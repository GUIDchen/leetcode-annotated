# 题目：54. 螺旋矩阵（Spiral Matrix）
# 思路：模拟。用方向数组表示右、下、左、上四个方向，每走一步就检查下一步是否越界或已访问，是就顺时针转向。
# 时间复杂度：O(m*n)，每个格子恰好访问一次；空间复杂度：O(m*n)，额外的访问标记数组。
class Solution:  # LeetCode 约定的题解类
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:  # matrix 为 m 行 n 列的矩阵，按螺旋顺序返回其中的元素
        m, n = len(matrix), len(matrix[0])  # m 是行数，n 是列数
        dirs = (0, 1, 0, -1, 0)  # 方向数组：右、下、左、上；第 k 个方向的行增量是 dirs[k]，列增量是 dirs[k+1]
        vis = [[False] * n for _ in range(m)]  # 访问标记矩阵，避免重复取同一个格子
        i = j = k = 0  # 当前位置 (i, j) 与当前方向下标 k，从 (0,0) 向右开始
        ans = []  # 按螺旋顺序保存结果
        for _ in range(m * n):  # 一共要取 m*n 个格子，每轮取一个
            ans.append(matrix[i][j])  # 记录当前格子的值
            vis[i][j] = True  # 标记当前格子已访问
            x, y = i + dirs[k], j + dirs[k + 1]  # 试探沿当前方向走一步的位置
            if x < 0 or x >= m or y < 0 or y >= n or vis[x][y]:  # 越界或已访问过，说明需要顺时针转弯
                k = (k + 1) % 4  # 顺时针切到下一个方向（右→下→左→上循环）
            i += dirs[k]  # 按（可能刚更新过的）方向移动行坐标
            j += dirs[k + 1]  # 按同方向移动列坐标
        return ans  # 返回螺旋顺序的结果
