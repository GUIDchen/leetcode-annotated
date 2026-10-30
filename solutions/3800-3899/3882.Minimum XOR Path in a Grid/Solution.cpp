// 3882. 网格图中最小异或路径 / Minimum XOR Path in a Grid
// 核心思路：按最大值的二进制位数确定异或值上界，用三维布尔 DP 记录每格可达的异或值，最后取终点的最小可达值。
// 复杂度：时间 O(m * n * 2^b)（b 为最大值的二进制位数），空间 O(m * n * 2^b)。
class Solution {  // 定义题解类
public:  // 公有接口
    int minCost(vector<vector<int>>& grid) {  // 返回从左上角到右下角路径异或值的最小可能值
        int m = grid.size(), n = grid[0].size();  // 网格行数与列数
        int mx = 0;  // 网格中的最大值
        for (auto& row : grid) {  // 遍历每一行
            for (int x : row) {  // 遍历行内每个数
                mx = max(mx, x);  // 更新最大值
            }  // 内层循环结束
        }  // 外层循环结束
        mx = 1 << bit_width(static_cast<unsigned>(mx));  // 异或值上界：不小于最大值的 2 的幂
        vector<vector<vector<char>>> f(m, vector<vector<char>>(n, vector<char>(mx, 0)));  // f[i][j][k] 表示走到 (i, j) 能否得到异或值 k
        f[0][0][grid[0][0]] = 1;  // 起点异或值只含起点自身的值
        for (int i = 0; i < m; i++) {  // 枚举行
            for (int j = 0; j < n; j++) {  // 枚举列
                int x = grid[i][j];  // 当前格子的值
                if (i > 0 || j > 0) {  // 起点已初始化，跳过
                    for (int k = 0; k < mx; k++) {  // 枚举目标异或值
                        if (i > 0 && f[i - 1][j][k ^ x]) {  // 从上方转移：上一步异或值须为 k ^ x
                            f[i][j][k] = 1;  // 标记该异或值可达
                        }  // 上方判断结束
                        if (j > 0 && f[i][j - 1][k ^ x]) {  // 从左方转移：左一步异或值须为 k ^ x
                            f[i][j][k] = 1;  // 标记该异或值可达
                        }  // 左方判断结束
                    }  // 异或值枚举结束
                }  // 起点判断结束
            }  // 列枚举结束
        }  // 行枚举结束
        for (int k = 0;; k++) {  // 从小到大寻找最小可达异或值
            if (f[m - 1][n - 1][k]) {  // 终点可以得到异或值 k
                return k;  // 该值即为最小异或和
            }  // if 分支结束
        }  // 查找循环结束
    }  // 方法结束
};  // 类定义结束