# 题目：892. 三维形体的表面积（Surface Area of 3D Shapes）
# 核心思路：每个高度非零的格子先算独立柱子的表面积 2+4v，再减去与上方、左方柱子重叠的贴合面。
# 时间复杂度：O(n^2)，遍历整个 n×n 网格；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def surfaceArea(self, grid: List[List[int]]) -> int:  # grid：二维网格，grid[i][j] 是该位置堆叠的立方体个数
        ans = 0  # 累计表面积
        for i, row in enumerate(grid):  # 逐行枚举，i 是行号，row 是该行
            for j, v in enumerate(row):  # 逐列枚举，j 是列号，v 是该格的高度
                if v:  # 高度为 0 的格子不产生表面，跳过
                    ans += 2 + v * 4  # 独立柱子：上下两个底面 + 每个立方体四个侧面
                    if i:  # 上方存在相邻柱子
                        ans -= min(v, grid[i - 1][j]) * 2  # 贴合的部分被遮住，两侧各减较矮的高度
                    if j:  # 左方存在相邻柱子
                        ans -= min(v, grid[i][j - 1]) * 2  # 同理减去与左方柱子的贴合面
        return ans  # 返回总表面积
