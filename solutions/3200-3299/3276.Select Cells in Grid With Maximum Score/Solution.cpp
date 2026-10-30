// 题目：3276. 选择矩阵中单元格的最大得分（Select Cells in Grid With Maximum Score）
// 思路：按数值从小到大做状压 DP，f[i][j] 表示只考虑数值 1..i、已占用行集合为 j 时的最大得分，每行最多用一次。
// 时间复杂度：O(V · 2^m · m)，V 为矩阵中的最大数值；空间复杂度：O(V · 2^m)，即 DP 表的规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxScore(vector<vector<int>>& grid) {  // grid：共 m 行的矩阵
        int m = grid.size();  // 行数，也是状态压缩的位数
        int mx = 0;  // 矩阵中出现过的最大值，决定 DP 的数值上界
        bool g[101][11]{};  // g[x][i] 表示数值 x 是否出现在第 i 行
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int x : grid[i]) {  // 遍历该行的每个元素
                g[x][i] = true;  // 标记数值 x 出现在第 i 行
                mx = max(mx, x);  // 更新出现过的最大值
            }
        }
        int f[mx + 1][1 << m];  // f[i][j]：只考虑数值 1..i、已占用行集合为 j 时的最大得分
        memset(f, 0, sizeof(f));  // 初始化为 0：什么都不选时得分为 0
        for (int i = 1; i <= mx; ++i) {  // 按数值从小到大枚举
            for (int j = 0; j < 1 << m; ++j) {  // 枚举所有可能的已占用行集合
                f[i][j] = f[i - 1][j];  // 不选数值 i，直接继承上一层的答案
                for (int k = 0; k < m; ++k) {  // 尝试把数值 i 放在第 k 行
                    if (g[i][k] && (j >> k & 1) == 1) {  // 数值 i 确实在第 k 行，且第 k 行已被占用（需要先撤销）
                        f[i][j] = max(f[i][j], f[i - 1][j ^ 1 << k] + i);  // 撤销第 k 行后再加上本次得分 i
                    }
                }
            }
        }
        return f[mx][(1 << m) - 1];  // 取所有行都被占用的状态：用满每一行不会更差，故它就是最优解
    }
};
