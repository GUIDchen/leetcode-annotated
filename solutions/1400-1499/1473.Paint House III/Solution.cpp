// 题目：1473. 粉刷房子 III（Paint House III）
// 思路：三维 DP，f[i][j][k] 表示刷完前 i+1 个房子、第 i 个房子颜色为 j、且恰好形成 k 个颜色街区时的最小花费；逐个房子按「同色不增街区 / 异色街区加一」转移。
// 时间复杂度：O(m * n^2 * target)，空间复杂度：O(m * n * target)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {  // houses：各房子颜色（0 表示待刷）；cost：刷色价格；m：房子数；n：颜色数；target：目标街区数
        int f[m][n + 1][target + 1];  // DP 表：颜色用 1..n 编号，街区数用 1..target，第 0 位留作哨兵
        memset(f, 0x3f, sizeof(f));  // 全部置为大数（视为无穷大），表示这些状态还不可达
        if (houses[0] == 0) {  // 第一个房子没有预涂颜色，可以任意选色
            for (int j = 1; j <= n; ++j) {  // 枚举第一个房子所刷的颜色 j
                f[0][j][1] = cost[0][j - 1];  // 只有 1 个街区，花费就是刷色价格（cost 的颜色下标从 0 开始）
            }
        } else {  // 第一个房子已经有颜色，不能改动
            f[0][houses[0]][1] = 0;  // 颜色固定、街区数为 1、额外花费为 0
        }
        for (int i = 1; i < m; ++i) {  // 从第二个房子开始逐个向后转移
            if (houses[i] == 0) {  // 当前房子未刷，需要枚举它刷什么颜色
                for (int j = 1; j <= n; ++j) {  // 枚举当前房子选的颜色 j
                    for (int k = 1; k <= min(target, i + 1); ++k) {  // 枚举街区数 k；前 i+1 个房子最多形成 i+1 个街区，最多只关心到 target
                        for (int j0 = 1; j0 <= n; ++j0) {  // 枚举前一个房子的颜色 j0
                            if (j == j0) {  // 与前一个房子同色，街区数不增加
                                f[i][j][k] = min(f[i][j][k], f[i - 1][j][k] + cost[i][j - 1]);  // 继承上一房子的花费，再叠加本次刷色价格
                            } else {  // 与前一个房子异色，街区数加一
                                f[i][j][k] = min(f[i][j][k], f[i - 1][j0][k - 1] + cost[i][j - 1]);  // 由 k-1 个街区的状态转移而来
                            }
                        }
                    }
                }
            } else {  // 当前房子已有预涂颜色，颜色不需要枚举
                int j = houses[i];  // 当前房子被固定的颜色
                for (int k = 1; k <= min(target, i + 1); ++k) {  // 枚举街区数 k
                    for (int j0 = 1; j0 <= n; ++j0) {  // 枚举前一个房子的颜色 j0
                        if (j == j0) {  // 同色，街区数保持不变
                            f[i][j][k] = min(f[i][j][k], f[i - 1][j][k]);  // 不额外花钱，直接继承
                        } else {  // 异色，街区数加一
                            f[i][j][k] = min(f[i][j][k], f[i - 1][j0][k - 1]);  // 从 k-1 个街区的状态转移
                        }
                    }
                }
            }
        }
        int ans = 0x3f3f3f3f;  // 用一个足够大的数作为答案初值
        for (int j = 1; j <= n; ++j) {  // 最后一个房子的颜色可以任选
            ans = min(ans, f[m - 1][j][target]);  // 在所有颜色中取「街区数恰好为 target」的最小花费
        }
        return ans == 0x3f3f3f3f ? -1 : ans;  // 仍为初值说明无解，按题目要求返回 -1
    }
};