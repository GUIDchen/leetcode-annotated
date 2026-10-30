// 题目：1594. 矩阵的最大非负积（Maximum Non Negative Product in a Matrix）
// 思路：路径乘积的符号只由正负决定，逐格同时维护「最小积」与「最大积」，乘法时交叉取极值。
// 时间复杂度：O(m * n)，每个格子只转移一次；空间复杂度：O(m * n)，保存每个格子的最小积与最大积。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProductPath(vector<vector<int>>& grid) {  // grid 为 m 行 n 列、元素可正可负的矩阵
        int m = grid.size(), n = grid[0].size();  // 分别记录行数 m 与列数 n
        vector<vector<array<long long, 2>>> f(m, vector<array<long long, 2>>(n));  // f[i][j] 保存到达格子 (i, j) 时的最小积与最大积

        // 下面按行、列顺序做二维动态规划
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                long long x = grid[i][j];  // 当前格子的值，转成 long long 避免乘法溢出
                if (i == 0 && j == 0) {  // 左上角起点，没有前驱格子
                    f[i][j] = {x, x};  // 起点的最小积与最大积都等于自身
                    continue;  // 起点处理完，跳过后面的转移
                }  // 起点分支结束

                // 先用极值初始化，便于下面不断取 min 与 max
                long long mn = LLONG_MAX, mx = LLONG_MIN;  // 最小积初值取最大数、最大积初值取最小数，方便后续取 min/max

                // 从上方格子转移
                if (i > 0) {  // 存在上方格子
                    auto [a, b] = f[i - 1][j];  // 解构：a 是最小积，b 是最大积
                    mn = min(mn, min(a * x, b * x));  // 乘以当前值可能反号，最小值取这两种乘积的较小者
                    mx = max(mx, max(a * x, b * x));  // 最大值同理取两种乘积中的较大者
                }  // 上方转移结束

                // 从左侧格子转移
                if (j > 0) {  // 存在左侧格子
                    auto [a, b] = f[i][j - 1];  // 解构左侧格子的最小积与最大积
                    mn = min(mn, min(a * x, b * x));  // 用左侧转移结果更新最小值
                    mx = max(mx, max(a * x, b * x));  // 用左侧转移结果更新最大值
                }  // 左侧转移结束

                // 上下左右两类前驱都算完，写入当前格子的最终结果
                f[i][j] = {mn, mx};  // 按 {最小积, 最大积} 的顺序写入当前格子
            }  // 列循环结束
        }  // 行循环结束

        // 右下角的最大积就是答案
        long long ans = f[m - 1][n - 1][1];  // 取右下角结果中的最大积
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        return ans < 0 ? -1 : ans % mod;  // 无法得到非负积返回 -1，否则对 1e9+7 取模
    }  // 方法结束
};  // 类结束
