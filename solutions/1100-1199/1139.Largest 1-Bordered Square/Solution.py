# 题目：1139. 最大的以 1 为边界的正方形（Largest 1-Bordered Square）
# 思路：先预处理每个格子向右、向下的连续 1 长度，再从大到小枚举边长 k，用四条边的连续长度做判定。
# 时间复杂度：O(m*n*min(m,n))；空间复杂度：O(m*n)。
class Solution:  # LeetCode 约定的题解类
    def largest1BorderedSquare(self, grid: List[List[int]]) -> int:  # grid 是 0/1 矩阵，返回边界全为 1 的最大正方形面积
        m, n = len(grid), len(grid[0])  # 矩阵的行数与列数
        down = [[0] * n for _ in range(m)]  # down[i][j]：从 (i,j) 向下连续 1 的个数
        right = [[0] * n for _ in range(m)]  # right[i][j]：从 (i,j) 向右连续 1 的个数
        for i in range(m - 1, -1, -1):  # 从最后一行往上递推，保证下方值已算好
            for j in range(n - 1, -1, -1):  # 从最后一列往左递推，保证右方值已算好
                if grid[i][j]:  # 当前格是 1 才有连续长度
                    down[i][j] = down[i + 1][j] + 1 if i + 1 < m else 1  # 下方还有行就接上下方格子的值加 1，否则到底只算 1 个
                    right[i][j] = right[i][j + 1] + 1 if j + 1 < n else 1  # 右方还有列就接上右方格子的值加 1，否则到边界只算 1 个
        for k in range(min(m, n), 0, -1):  # 边长从 min(m,n) 开始递减，首个成立的即最大值
            for i in range(m - k + 1):  # 枚举左上角行，上界 m-k 防越界
                for j in range(n - k + 1):  # 枚举左上角列，上界 n-k 防越界
                    if (  # 四条边都要够长 k 才可能成立，下面逐条判断左边、上边、下边、右边
                        down[i][j] >= k  # 左边：左上角向下的长度（down[i][j]）
                        and right[i][j] >= k  # 上边：左上角向右的长度（right[i][j]）
                        and right[i + k - 1][j] >= k  # 下边：左下角向右的长度
                        and down[i][j + k - 1] >= k  # 右边：右上角向下的长度
                    ):  # 四条边都够 k，条件成立
                        return k * k  # 边长从大到小枚举，第一个可行的就是最大正方形，返回面积
        return 0  # 矩阵里没有 1，返回 0
