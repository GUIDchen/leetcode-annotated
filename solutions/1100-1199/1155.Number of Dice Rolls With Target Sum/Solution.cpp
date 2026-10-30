// 题目：1155. 掷骰子等于目标和的方法数（Number of Dice Rolls With Target Sum）
// 思路：动态规划，f[i][j] 表示 i 颗骰子掷出和为 j 的方案数，按最后一颗骰子的点数 1..k 转移。
// 时间复杂度：O(n·target·k)；空间复杂度：O(n·target)。
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    int numRollsToTarget(int n, int k, int target) {  // n 颗骰子、每颗 1..k 面，求掷出和为 target 的方案数（结果取模）
        const int mod = 1e9 + 7;  // 取模常数 1e9+7，防止方案数溢出
        int f[n + 1][target + 1];  // f[i][j]：用 i 颗骰子掷出和为 j 的方案数（变长数组）
        memset(f, 0, sizeof f);  // 全部清零，表示还没有任何方案
        f[0][0] = 1;  // 边界：0 颗骰子只有和为 0 这一种空方案
        for (int i = 1; i <= n; ++i) {  // 逐颗增加骰子
            for (int j = 1; j <= min(target, i * k); ++j) {  // 枚举 i 颗骰子可达的和 j，上界受 i*k 与 target 限制
                for (int h = 1; h <= min(j, k); ++h) {  // 枚举第 i 颗骰子的点数 h，最大到 k 且不超过当前和 j
                    f[i][j] = (f[i][j] + f[i - 1][j - h]) % mod;  // 转移：前 i-1 颗和为 j-h、第 i 颗出 h，累加后取模
                }  // 结束点数枚举
            }  // 结束和枚举
        }  // 结束骰子枚举
        return f[n][target];  // 答案：n 颗骰子凑出 target 的方案数
    }  // 方法结束
};  // 类定义结束