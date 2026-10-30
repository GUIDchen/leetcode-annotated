// 题目：2304. 网格中的最小路径代价（Minimum Path Cost in a Grid）
// 思路：按行动态规划，f[k] 表示到达上一行第 k 列的最小总代价；本行每列 j 枚举全部来源列 k 做转移取最小，逐行滚动更新。
// 时间复杂度：O(m * n^2)，m 行每行 n^2 次转移；空间复杂度：O(n)，只用两行的滚动数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {  // grid：每格的代价；moveCost：由上一行某格的值移动到本行某列的额外代价
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数
        const int inf = 1 << 30;  // 用一个足够大的数表示“不可达”，1 << 30 约 10 亿，不会溢出 int 的加法范围
        vector<int> f = grid[0];  // 初始化：第一行只能从本格开始，代价就是格子本身的值
        for (int i = 1; i < m; ++i) {  // 从第二行开始逐行向下推进（第 0 行已初始化）
            vector<int> g(n, inf);  // g 保存到达本行各列的最小代价，先全部置为无穷大
            for (int j = 0; j < n; ++j) {  // 枚举本行要落入的列 j
                for (int k = 0; k < n; ++k) {  // 枚举上一行的来源列 k，尝试所有可能的前驱
                    g[j] = min(g[j], f[k] + moveCost[grid[i - 1][k]][j] + grid[i][j]);  // 转移：上一行第 k 列的代价 + 从 grid[i-1][k] 这一格值移动到第 j 列的代价 + 本格代价，取最小值
                }  // 来源列枚举结束
            }  // 目标列枚举结束
            f = move(g);  // 把本行结果换到 f 上，进入下一轮（move 避免整体拷贝）
        }  // 行枚举结束
        return *min_element(f.begin(), f.end());  // 最后一行任意一列都可以作为终点，取其中最小的代价
    }  // 方法结束
};  // 类定义结束