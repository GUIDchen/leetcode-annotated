// 题目：2836. 在传球游戏中最大化函数值（Maximize Value of Function in a Ball Passing Game）
// 思路：二进制倍增。f[i][j] 表示从 i 走 2^j 步到达的位置，g[i][j] 为这 2^j 步路径上的号码和；把 k 按二进制位拆成若干段跳跃后拼接。
// 时间复杂度：O(n log k)，建表与累计均为 n * log k；空间复杂度：O(n log k)，两张倍增表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {  // receiver[i] 是 i 传球的目标；k 是传球次数
        int n = receiver.size(), m = 64 - __builtin_clzll(k);  // n 为人数；m 为 k 的二进制位数，即倍增表的层数
        vector<vector<int>> f(n, vector<int>(m));  // f[i][j]：从 i 出发走 2^j 步后到达的位置
        vector<vector<long long>> g(n, vector<long long>(m));  // g[i][j]：走这 2^j 步途中经过的号码之和（含起点、不含终点）
        for (int i = 0; i < n; ++i) {  // 初始化倍增表第 0 层，即只走 1 步的情况
            f[i][0] = receiver[i];  // 走 1 步后停在传球目标上
            g[i][0] = i;  // 只走 1 步时，途中的号码只有起点自己
        }
        for (int j = 1; j < m; ++j) {  // 逐层递推走 2^j 步
            for (int i = 0; i < n; ++i) {  // 枚举每个起点
                f[i][j] = f[f[i][j - 1]][j - 1];  // 先走 2^(j-1) 步，再从这个落点走 2^(j-1) 步
                g[i][j] = g[i][j - 1] + g[f[i][j - 1]][j - 1];  // 两段路径的号码之和直接相加
            }
        }
        long long ans = 0;  // 记录所有起点中的最大函数值
        for (int i = 0; i < n; ++i) {  // 枚举每个起点 i 作为函数值的起点
            int p = i;  // p 记录当前所在的球员编号
            long long t = 0;  // t 记录已经累计的途中号码之和
            for (int j = 0; j < m; ++j) {  // 按 k 的二进制位从低到高拆出要跳的段
                if (k >> j & 1) {  // 第 j 位为 1，说明需要跳一段 2^j 步
                    t += g[p][j];  // 累加这一段沿途的号码之和
                    p = f[p][j];  // 位置随之前进 2^j 步
                }
            }
            ans = max(ans, p + t);  // 函数值等于终点号码加上途中号码之和，取最大
        }
        return ans;  // 返回最大函数值
    }
};