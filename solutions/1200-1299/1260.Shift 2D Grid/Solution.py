# 题目：1260. 二维网格迁移（Shift 2D Grid）
# 思路：把网格当作长度 m·n 的一维数组，元素右移 k 位后按 divmod 还原成新行列坐标，取模完成首尾循环。
# 时间复杂度：O(mn)，每个格子只处理一次；空间复杂度：O(mn)，另建同样大小的答案网格。
class Solution:  # LeetCode 约定的题解类
    def shiftGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:  # grid 是二维网格，k 是迁移次数
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        ans = [[0] * n for _ in range(m)]  # 预先分配同样尺寸的答案网格，避免原地修改污染后续读取
        for i, row in enumerate(grid):  # 同时取得行下标 i 与整行内容 row
            for j, v in enumerate(row):  # 同时取得列下标 j 与该格的值 v
                x, y = divmod((i * n + j + k) % (m * n), n)  # i*n+j 把坐标压成一维，右移 k 位后对总格数取模，再用 divmod 一次算出新行 x 与新列 y
                ans[x][y] = v  # 把原值写入迁移后的位置
        return ans  # 返回迁移后的网格
