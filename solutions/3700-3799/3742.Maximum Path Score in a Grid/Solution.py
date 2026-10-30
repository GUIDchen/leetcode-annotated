# 题目：3742. 网格中得分最大的路径（Maximum Path Score in a Grid）
# 核心思路：记忆化搜索，dfs(i, j, k) 表示「从 (0,0) 走到 (i,j) 且还剩 k 点花费额度」时的最大分数；当前格的分数累加进去，值大于 0 时消耗一次额度；越界或额度为负说明路径非法，返回负无穷以便被 max 淘汰。
# 复杂度：时间 O(m*n*k)，每个状态只算一次；空间 O(m*n*k)，缓存表加上递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxPathScore(self, grid: List[List[int]], k: int) -> int:  # grid：取值 0/1/2 的网格；k：总花费上限；返回总花费不超过 k 时的最大分数，无合法路径则返回 -1
        @cache  # 记忆化装饰器，等价于手工维护的 dp 表
        def dfs(i: int, j: int, k: int) -> int:  # 从 (0,0) 走到 (i,j)、还剩 k 点花费额度时的最大分数
            if i < 0 or j < 0 or k < 0:  # 越界或花费额度已经用尽
                return -inf  # 该前缀路径非法，返回负无穷
            if i == 0 and j == 0:  # 到达起点
                return 0  # 起点之前还没有累积任何分数
            res = grid[i][j]  # 先计入当前格子的分数
            if grid[i][j]:  # 当前格子值不为 0，需要花费 1 点
                k -= 1  # 消耗一个花费额度
            a = dfs(i - 1, j, k)  # 从上边一格过来的最大分数
            b = dfs(i, j - 1, k)  # 从左边一格过来的最大分数
            res += max(a, b)  # 接上更优的那条前缀路径
            return res  # 返回当前状态的最大分数

        ans = dfs(len(grid) - 1, len(grid[0]) - 1, k)  # 从右下角开始反推整条路径的最大分数
        dfs.cache_clear()  # 清空缓存，避免多次调用之间互相污染
        return -1 if ans < 0 else ans  # 答案为负说明不存在合法路径，返回 -1
