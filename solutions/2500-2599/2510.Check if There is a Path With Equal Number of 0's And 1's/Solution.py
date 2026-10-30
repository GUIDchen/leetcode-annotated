# 题目：2510. 检查是否有路径经过相同数量的 0 和 1（Check if There is a Path With Equal Number of 0's And 1's）
# 思路：路径长度固定为 m+n-1 个格子，为奇数时必然无解；否则记一半为 s，用 @cache 记忆化深搜「已累计 1 的个数」，超过 s 即剪枝，到终点时 1 的个数恰为 s 即成功。
# 时间复杂度：O(m * n * (m + n))，状态数为格子数乘累计 1 的个数；空间复杂度：O(m * n * (m + n))，缓存占用。
class Solution:  # LeetCode 约定的题解类
    def isThereAPath(self, grid: List[List[int]]) -> bool:  # grid 是只含 0 和 1 的矩阵，判断是否存在 0 与 1 数量相等的路径
        @cache  # 自动记忆化装饰器：相同的 (i, j, k) 只会真正计算一次
        def dfs(i, j, k):  # 表示从 (i, j) 出发、已经累计 k 个 1 时能否走到终点
            if i >= m or j >= n:  # 越界说明这条走法非法
                return False  # 该方向不可走
            k += grid[i][j]  # 进入当前格子，把它累加到 1 的计数上
            if k > s or i + j + 1 - k > s:  # 1 或 0 的个数已超过一半，后续无法再平衡，剪枝
                return False  # 该状态不可能成功
            if i == m - 1 and j == n - 1:  # 到达右下角终点
                return k == s  # 1 恰好为一半即成功（0 自然也恰为一半）
            return dfs(i + 1, j, k) or dfs(i, j + 1, k)  # 向下或向右任一方向能走通即可

        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数（dfs 调用时才求值，故可写在后面）
        s = m + n - 1  # 从左上角到右下角路径上的格子总数
        if s & 1:  # 格子数为奇数时无法平分 0 与 1
            return False  # 直接无解
        s >>= 1  # s 变为路径上应当出现的 1 的个数
        return dfs(0, 0, 0)  # 从左上角出发，初始已累计 1 的个数为 0
