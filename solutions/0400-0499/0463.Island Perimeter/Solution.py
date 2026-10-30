# 题目：463. 岛屿的周长（Island Perimeter）
# 思路：每个陆地格先按 4 条边计数，再对「右邻、下邻」也是陆地的边各减 2，使每对相邻陆地只被扣一次重复边。
# 时间复杂度：O(mn)，需要遍历整个网格；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def islandPerimeter(self, grid: List[List[int]]) -> int:  # grid：0/1 网格，1 表示陆地
        m, n = len(grid), len(grid[0])  # m 为行数、n 为列数，题目保证网格非空
        ans = 0  # ans 累计周长
        for i in range(m):  # 逐行扫描
            for j in range(n):  # 逐列扫描
                if grid[i][j] == 1:  # 只处理陆地格
                    ans += 4  # 一个孤立的陆地格贡献 4 条边
                    if i < m - 1 and grid[i + 1][j] == 1:  # 下方也是陆地：两条公共边不计入周长
                        ans -= 2  # 递减两条边
                    if j < n - 1 and grid[i][j + 1] == 1:  # 右方也是陆地：两条公共边不计入周长
                        ans -= 2  # 递减两条边
        return ans  # 返回总周长
