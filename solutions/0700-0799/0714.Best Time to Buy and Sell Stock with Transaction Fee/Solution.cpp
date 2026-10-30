// 题目：714. 买卖股票的最佳时机含手续费（Best Time to Buy and Sell Stock with Transaction Fee）
// 核心思路：记忆化搜索。状态为「第 i 天 + 当前是否持股」，每天要么不操作、要么买入（空仓转持股）、要么卖出（持股转空仓并付手续费），取收益最大者。
// 时间复杂度：O(n)，每个状态只计算一次（共 2n 个状态）；空间复杂度：O(n)，记忆化数组与递归栈深度均为 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的接口区
    int maxProfit(vector<int>& prices, int fee) {  // prices 是每日股价，fee 是每笔交易的固定手续费，返回能获得的最大利润
        int n = prices.size();  // 天数，用于确定记忆化数组的大小
        int f[n][2];  // f[i][j]：第 i 天、持股状态为 j（1 表示持股、0 表示空仓）时的最大收益
        memset(f, -1, sizeof(f));  // 用 -1 表示「尚未计算」，作为记忆化的哨兵值
        function<int(int, int)> dfs = [&](int i, int j) {  // 递归函数：从第 i 天、持股状态 j 出发能获得的最大收益
            if (i >= prices.size()) {  // 已经越过最后一天，不能再交易
                return 0;  // 递归边界：收益为 0
            }  // 结束边界判断
            if (f[i][j] != -1) {  // 该状态之前算过，可直接取出缓存值
                return f[i][j];  // 返回缓存结果，避免重复计算
            }  // 结束缓存判断
            int ans = dfs(i + 1, j);  // 选择「今天不操作」，状态保持不变
            if (j) {  // 当前持股，只能考虑卖出（或继续持有）
                ans = max(ans, prices[i] + dfs(i + 1, 0) - fee);  // 卖出：拿到今日股价并付手续费，明天变为空仓
            } else {  // 当前空仓，只能考虑买入
                ans = max(ans, -prices[i] + dfs(i + 1, 1));  // 买入：付出今日股价，明天变为持股
            }  // 结束持股状态分支
            return f[i][j] = ans;  // 把结果写入缓存并返回
        };  // lambda 定义结束（末尾分号属于赋值语句）
        return dfs(0, 0);  // 从第 0 天、空仓状态开始求解
    }  // 结束 maxProfit 方法
};  // 结束 Solution 类定义
