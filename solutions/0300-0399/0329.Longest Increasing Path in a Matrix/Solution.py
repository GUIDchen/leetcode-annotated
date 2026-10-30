# 题目：329. 矩阵中的最长递增路径（Longest Increasing Path in a Matrix）
# 思路：记忆化 DFS；f[i][j] 表示以 (i,j) 为起点的最长递增路径，向四个方向找严格更大的格子取最大值再加一，每个格子只算一次。
# 时间复杂度：O(m*n)，每个格子只被计算一次；空间复杂度：O(m*n)，缓存加上递归栈。
class Solution:    # LeetCode 约定的题解类
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:    # matrix：二维矩阵，返回其中最长的严格递增路径长度
        @cache    # @cache 自动记忆化：同一个 (i, j) 只会真正深搜一次
        def dfs(i: int, j: int) -> int:    # 返回以 (i, j) 为起点的最长递增路径长度
            ans = 0    # 记录从四个方向能延伸出的最长长度
            for a, b in pairwise((-1, 0, 1, 0, -1)):    # pairwise 把方向数组两两配对，得到四个方向向量
                x, y = i + a, j + b    # 相邻格子的坐标
                if 0 <= x < m and 0 <= y < n and matrix[x][y] > matrix[i][j]:    # 越界检查 + 下一个格子的值必须严格更大才能走过去
                    ans = max(ans, dfs(x, y))    # 取所有可行方向中的最大值
            return ans + 1    # +1 表示把自己这一格也算进路径长度

        m, n = len(matrix), len(matrix[0])    # 行列数：dfs 里引用它们，调用时已赋值（闭包延迟绑定）
        return max(dfs(i, j) for i in range(m) for j in range(n))    # 以每个格子为起点求最长路径，取全局最大值
