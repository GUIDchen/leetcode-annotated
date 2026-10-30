// 题目：3888. 使所有网格元素相等的最小操作次数（Minimum Operations to Make All Grid Elements Equal）
// 思路：每次把 k×k 子矩阵整体加 1，数值只能增大，故最终目标值只能是最大值或最大值+1；对固定目标值从左上到右下贪心补齐，用二维差分数组 O(1) 完成整块加一。
// 时间复杂度：O(m × n)，只需两次可行性检查；空间复杂度：O(m × n)，存放二维差分数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minOperations(vector<vector<int>>& grid, int k) {  // grid：m×n 网格；k：每次操作所选子矩阵的边长
        int m = grid.size();  // 网格行数
        int n = grid[0].size();  // 网格列数
        int mx = grid[0][0];  // 先以左上角元素作为最大值初值
        for (auto& row : grid) {  // 遍历每一行
            for (int val : row) {  // 遍历该行中的每个元素
                mx = max(mx, val);  // 更新全局最大值：目标值不可能小于它
            }  // 结束内层列遍历
        }  // 结束外层行遍历

        auto check = [&](int target) -> long long {  // 定义闭包 check(target)：判断能否把所有元素都变成 target，可行则返回总操作次数
            vector<vector<long long>> diff(m + 2, vector<long long>(n + 2, 0));  // 二维差分数组，额外多开两行两列以省去边界判断
            long long total_ops = 0;  // 累计操作次数，也就是所有格子被加的总次数

            for (int i = 1; i <= m; ++i) {  // 按行从上到下扫描（差分下标从 1 开始，便于处理第 0 行）
                for (int j = 1; j <= n; ++j) {  // 按列从左到右扫描
                    diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];  // 二维前缀和还原：得到当前格子此前被覆盖的总次数
                    long long cur_val = grid[i - 1][j - 1] + diff[i][j];  // 当前格子的真实值 = 原值 + 之前所有 k×k 操作带来的增量

                    if (cur_val > target) {  // 只能增加，已经超过 target 就不可能再拉平
                        return -1;  // 该目标值不可行，返回 -1
                    }  // 结束“超过 target”的判断

                    if (cur_val < target) {  // 当前值偏小，需要继续补齐
                        if (i + k - 1 > m || j + k - 1 > n) {  // 以 (i, j) 为左上角的 k×k 子矩阵必须完整落在网格内
                            return -1;  // 子矩阵越界，说明这个格子无法补齐
                        }  // 结束越界判断

                        long long needed = target - cur_val;  // 需要补足的差值
                        total_ops += needed;  // 每补 1 算一次操作，累加进总操作数
                        diff[i][j] += needed;  // 差分数组单点加，表示从这里开始被覆盖 needed 次
                        diff[i + k][j] -= needed;  // 第 i+k 行减去 needed，撤销对下方的影响
                        diff[i][j + k] -= needed;  // 第 j+k 列减去 needed，撤销对右方的影响
                        diff[i + k][j + k] += needed;  // 右下角补回 needed，抵消前面两次减法（容斥）
                    }  // 结束“需要补齐”的分支
                }  // 结束列循环
            }  // 结束行循环

            return total_ops;  // 所有格子都恰好等于 target，返回总操作次数
        };  // 结束闭包定义

        for (int t = mx; t <= mx + 1; ++t) {  // 目标值只需尝试最大值 mx 与 mx+1 这两种可能
            long long res = check(t);  // 计算该目标值下的最少操作次数，-1 表示不可行
            if (res != -1) {  // 找到可行方案
                return res;  // 立即返回该最少操作次数
            }  // 结束可行性判断
        }  // 结束目标值枚举

        return -1;  // 两种目标值都不可行
    }  // 结束方法
};  // 结束类
