// 题目：883. 三维形体投影面积（Projection Area of 3D Shapes）
// 思路：一次遍历同时累加三种投影：俯视面积统计高度大于 0 的格子，正视与侧视分别累加每行、每列的最大高度。
// 时间复杂度：O(n²)，遍历整个 n×n 网格；空间复杂度：O(1)，只用了几个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int projectionArea(vector<vector<int>>& grid) {  // grid：n×n 的高度矩阵，grid[i][j] 表示该格子上立方体的个数
        int xy = 0, yz = 0, zx = 0;  // xy 是俯视（xy 平面）面积，yz、zx 是另外两个方向的侧视面积
        for (int i = 0, n = grid.size(); i < n; ++i) {  // 逐行扫描，n 为边长
            int maxYz = 0, maxZx = 0;  // 第 i 行的最大高度、第 i 列（借助转置下标）的最大高度
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                xy += grid[i][j] > 0;  // 高度大于 0 说明俯视图上有这一格
                maxYz = max(maxYz, grid[i][j]);  // 第 i 行的最高值贡献正视投影
                maxZx = max(maxZx, grid[j][i]);  // 第 i 列的最高值贡献侧视投影（行、列下标互换）
            }
            yz += maxYz;  // 累加第 i 行的正视投影
            zx += maxZx;  // 累加第 i 列的侧视投影
        }
        return xy + yz + zx;  // 三种投影面积之和即为答案
    }  // 方法结束
};  // 类定义结束