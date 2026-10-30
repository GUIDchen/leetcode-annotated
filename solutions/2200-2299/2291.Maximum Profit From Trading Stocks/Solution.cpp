// 题目：2291. 最大股票收益（Maximum Profit From Trading Stocks）
// 核心思路：把每只股票看成「重量 present[i]、价值 future[i]-present[i]」的物品，用 0-1 背包求预算内的最大收益。
// 时间复杂度：O(n * budget)，两层循环遍历股票与预算；空间复杂度：O(n * budget)，使用二维 dp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumProfit(vector<int>& present, vector<int>& future, int budget) {  // present：买入价数组；future：一年后的价格数组；budget：总预算
        int n = present.size();  // n：可选股票的数量
        int f[n + 1][budget + 1];  // f[i][j]：只考虑前 i 只股票、花费不超过 j 时能获得的最大收益
        memset(f, 0, sizeof f);  // 全部初始化为 0：一只股票都不买时收益为 0
        for (int i = 1; i <= n; ++i) {  // 逐只股票推进，对应 0-1 背包的物品维度
            for (int j = 0; j <= budget; ++j) {  // 枚举所有可能的预算上限 j
                f[i][j] = f[i - 1][j];  // 不买第 i 只股票：直接继承前 i-1 只的最优解
                if (j >= present[i - 1]) {  // 预算够买第 i 只股票时才考虑买入（present 下标从 0 开始故用 i-1）
                    f[i][j] = max(f[i][j], f[i - 1][j - present[i - 1]] + future[i - 1] - present[i - 1]);  // 买入收益增加 future-present，剩余预算 j-present 沿用上一行状态，与不买方案取较大值
                }
            }  // 结束预算枚举
        }  // 结束股票枚举
        return f[n][budget];  // 前 n 只股票、预算为 budget 时的最大收益
    }
};  // 结束 Solution 类定义