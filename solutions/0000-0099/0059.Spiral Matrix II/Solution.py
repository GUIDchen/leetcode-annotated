# 题目：59. 螺旋矩阵 II（Spiral Matrix II）
# 思路：模拟填数，(i, j) 从左上角出发，方向按「右→下→左→上」循环；每格先写值，再试探下一格，越界或已填则换向。
# 时间复杂度：O(n^2)，n*n 个格子各填一次；空间复杂度：O(1) 额外空间（结果矩阵本身占 O(n^2)）。
class Solution:  # LeetCode 约定的题解类
    def generateMatrix(self, n: int) -> List[List[int]]:  # n：矩阵边长，返回 n×n 的螺旋填充矩阵
        ans = [[0] * n for _ in range(n)]  # 结果矩阵，0 表示该格尚未填数
        dirs = (0, 1, 0, -1, 0)  # 方向表：相邻两项成对使用，(0,1) 右、(1,0) 下、(0,-1) 左、(-1,0) 上；末尾补 0 防越界
        i = j = k = 0  # 坐标从左上角 (0,0) 开始，k=0 表示初始方向为「向右」
        for v in range(1, n * n + 1):  # 依次填入 1 到 n*n
            ans[i][j] = v  # 先把当前数字写到当前格
            x, y = i + dirs[k], j + dirs[k + 1]  # 试探沿当前方向走一步会到哪里
            if x < 0 or x >= n or y < 0 or y >= n or ans[x][y]:  # 越界或下一格已有数字（非 0 为真）
                k = (k + 1) % 4  # 走到边界就顺时针转向；%4 保证方向编号只在 0~3 之间循环
            i, j = i + dirs[k], j + dirs[k + 1]  # 用转向后的方向真正前进一步
        return ans  # 数字填满即得到螺旋矩阵
