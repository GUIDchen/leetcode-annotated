# 题目：695. 岛屿的最大面积（Max Area of Island）
# 思路：遇到未标记的陆地就 DFS 淹掉整块连通区域并统计格子数，所有连通块面积的最大值就是答案。
# 时间复杂度：O(m * n)，每个格子只被访问一次；空间复杂度：O(m * n)，最坏情况下递归深度等于岛屿面积。
class Solution:  # LeetCode 约定的题解类
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:  # grid 中 0 是海水、1 是陆地，返回最大岛屿面积
        def dfs(i: int, j: int) -> int:  # 内层递归函数：返回从 (i, j) 出发能吞并的陆地面积
            if grid[i][j] == 0:  # 当前位置是海水，或已被访问过而被改成 0
                return 0  # 没有陆地，面积贡献为 0
            ans = 1  # 当前格子本身算 1 个单位面积
            grid[i][j] = 0  # 立刻标记为已访问，避免重复统计和无限递归
            dirs = (-1, 0, 1, 0, -1)  # 方向序列：相邻两项配对成 (dx, dy)，表示上、右、下、左
            for a, b in pairwise(dirs):  # pairwise 把序列切成 (-1,0)、(0,1)、(1,0)、(0,-1) 四组
                x, y = i + a, j + b  # 算出相邻格子的坐标
                if 0 <= x < m and 0 <= y < n:  # 只有坐标未越界才继续扩展
                    ans += dfs(x, y)  # 累加该方向上连通陆地的面积
            return ans  # 返回这一整块连通陆地的面积

        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数，供上面的边界判断使用
        return max(dfs(i, j) for i in range(m) for j in range(n))  # 枚举每个格子作为起点，取最大面积
