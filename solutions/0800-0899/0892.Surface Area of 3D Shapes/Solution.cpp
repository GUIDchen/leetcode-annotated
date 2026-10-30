// 题目：892. 三维形体的表面积（Surface Area of 3D Shapes）
// 核心思路：每个非零格子先按独立柱子算 2+4v，再减去与上方、左方相邻柱子贴合被遮住的侧面。
// 时间复杂度：O(n^2)，遍历整个 n×n 网格；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int surfaceArea(vector<vector<int>>& grid) {  // grid：n×n 网格，grid[i][j] 表示该格上堆叠的立方体个数
        int n = grid.size();  // 网格边长，行列数相同
        int ans = 0;  // 累计表面积
        for (int i = 0; i < n; ++i) {  // 逐行扫描每一行
            for (int j = 0; j < n; ++j) {  // 逐列扫描每一列
                if (grid[i][j]) {  // 高度为 0 的格子不产生表面，直接跳过
                    ans += 2 + grid[i][j] * 4;  // 先按独立柱子算：上下两个底面 + 每个立方体的四个侧面
                    if (i) ans -= min(grid[i][j], grid[i - 1][j]) * 2;  // 与上方相邻柱子贴合的面被遮住，较矮的高度两侧都要减
                    if (j) ans -= min(grid[i][j], grid[i][j - 1]) * 2;  // 与左方相邻柱子贴合的面同理
                }  // 结束非零格子的处理
            }
        }
        return ans;  // 返回总表面积
    }
};  // 类定义结束