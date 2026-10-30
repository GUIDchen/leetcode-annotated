# 题目：2684. 矩阵中移动的最大次数（Maximum Number of Moves in a Grid）
# 思路：按列做 BFS，用集合 q 记录上一列可以到达的行；逐列向右侧三个方向扩展严格更大的格子，集合为空时当前列号就是答案。
# 时间复杂度：O(m*n)，每个格子最多被访问常数次；空间复杂度：O(m)，两个集合最多存 m 行。
class Solution:  # LeetCode 约定的题解类
    def maxMoves(self, grid: List[List[int]]) -> int:  # grid 是行列递增移动的矩阵
        m, n = len(grid), len(grid[0])  # m、n 分别是行数与列数
        q = set(range(m))  # 第 0 列任意一行都可以作为起点
        for j in range(n - 1):  # 逐列向右推进，最多走到倒数第二列
            t = set()  # t 收集下一列可达的行
            for i in q:  # 遍历当前列所有可达的行
                for k in range(i - 1, i + 2):  # 尝试右下、右、右上三个方向
                    if 0 <= k < m and grid[i][j] < grid[k][j + 1]:  # 行号不越界且目标格严格更大才能移动
                        t.add(k)  # 记录下一列可达的行
            if not t:  # 下一列一个格子都到不了，说明走不动了
                return j  # 已经走了 j 步，返回 j
            q = t  # 把下一列集合并入当前集合，继续推进
        return n - 1  # 一直走到最后一列，共走了 n-1 步
