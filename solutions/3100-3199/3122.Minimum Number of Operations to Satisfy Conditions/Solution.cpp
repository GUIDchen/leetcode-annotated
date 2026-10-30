// 题目：3122. 使矩阵满足条件的最少操作次数（Minimum Number of Operations to Satisfy Conditions）
// 思路：按列做动态规划，f[i][j] 表示第 i 列全部改成 j 时前 i 列的最少修改次数，转移时要求相邻两列取值不同。
// 时间复杂度：O(n * 10 * 10 + m * n)，n 为列数、m 为行数；空间复杂度：O(n * 10)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperations(vector<vector<int>>& grid) {  // 返回使矩阵任意相邻格子（上下、左右）取值都不同的最少修改次数
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数；下面按「列」为单位做动态规划
        int f[n][10];  // f[i][j]：第 i 列最终全部改成 j 时，前 i 列（0..i）的最小修改次数
        memset(f, 0x3f, sizeof(f));  // 初始化为一个很大的值 0x3f3f3f3f，表示「尚未计算」
        for (int i = 0; i < n; ++i) {  // 逐列递推
            int cnt[10]{};  // cnt[x]：第 i 列中原始值等于 x 的格子个数
            for (int j = 0; j < m; ++j) {  // 遍历第 i 列的每一行
                ++cnt[grid[j][i]];  // 统计该列中各个数字出现的次数
            }  // 结束本列的数字统计
            if (i == 0) {  // 第一列没有前一列的约束，需要单独初始化
                for (int j = 0; j < 10; ++j) {  // 枚举第一列最终被改成的数字 j
                    f[i][j] = m - cnt[j];  // 保留原来的 cnt[j] 个，其余 m - cnt[j] 个都要修改
                }  // 结束第一列初始化
            } else {  // i > 0 时还必须保证与第 i-1 列的数字不同
                for (int j = 0; j < 10; ++j) {  // 枚举本列最终的数字 j
                    for (int k = 0; k < 10; ++k) {  // 枚举前一列最终的数字 k
                        if (k != j) {  // 只有 k != j 才允许转移，否则相邻格子仍相同
                            f[i][j] = min(f[i][j], f[i - 1][k] + m - cnt[j]);  // 用「前 i-1 列以 k 结尾的最优值 + 本列修改数」更新最小值
                        }  // 结束 if (k != j)
                    }  // 结束 k 的枚举
                }  // 结束 j 的枚举
            }  // 结束 else 分支
        }  // 结束逐列递推
        return *min_element(f[n - 1], f[n - 1] + 10);  // 最后一列取任意数字都合法，取 10 种情况中的最小值即为答案
    }  // 结束 minimumOperations 方法
};  // 结束 Solution 类