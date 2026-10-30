# 题目：576. 出界的路径数（Out of Boundary Paths）
# 核心思路：记忆化 DFS，dfs(i,j,k) 表示从 (i,j) 出发、还剩 k 步时走出边界的方案数，四方向转移并对 1e9+7 取模。
# 时间复杂度：O(m * n * maxMove)，每个状态只算一次；空间复杂度：O(m * n * maxMove) 的缓存。
class Solution:  # LeetCode 约定的题解类
    def findPaths(  # 返回从起点出发、最多走 maxMove 步后出界的路径数
        self, m: int, n: int, maxMove: int, startRow: int, startColumn: int  # 网格 m 行 n 列，步数上限 maxMove，起点 (startRow, startColumn)
    ) -> int:  # 返回路径数量对 1e9+7 取模的结果
        @cache  # 记忆化装饰器：相同的 (i, j, k) 只计算一次
        def dfs(i: int, j: int, k: int) -> int:  # 当前在 (i,j)，还剩 k 步
            if not 0 <= i < m or not 0 <= j < n:  # 链式比较判断行列是否越界
                return int(k >= 0)  # 已越界即成功走出边界，计为 1 条路径
            if k <= 0:  # 尚未出界但步数耗尽
                return 0  # 无法继续走，方案数为 0
            ans = 0  # 累计当前状态的出界方案数
            for a, b in pairwise(dirs):  # pairwise 把方向数组两两配对，得到四个 (行增量, 列增量)
                x, y = i + a, j + b  # 沿该方向走一步后的新坐标
                ans = (ans + dfs(x, y, k - 1)) % mod  # 累加子问题的答案并取模防溢出
            return ans  # 返回当前状态的方案数

        mod = 10**9 + 7  # 取模常量，答案需要它
        dirs = (-1, 0, 1, 0, -1)  # 环形方向数组：相邻两项组成一个方向增量
        return dfs(startRow, startColumn, maxMove)  # 从起点、剩余 maxMove 步开始递归求解
