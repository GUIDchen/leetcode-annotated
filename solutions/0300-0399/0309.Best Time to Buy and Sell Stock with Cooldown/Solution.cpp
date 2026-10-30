// 题目：309. 买卖股票的最佳时机含冷冻期（Best Time to Buy and Sell Stock with Cooldown）
// 思路：记忆化搜索。状态是 (天数, 是否持股)，每天在「不动 / 买入 / 卖出」中取收益最大者，卖出后跳到第 i+2 天。
// 时间复杂度：O(n)，共 2n 个状态；空间复杂度：O(n)，记忆化表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int maxProfit(vector<int>& prices) {  // prices 是每日股价，返回最大利润（卖出后隔一天才能再买）
        int n = prices.size();  // 天数
        int f[n][2];  // f[i][j]：第 i 天、持股状态为 j（0 空仓 / 1 持股）时的最大收益，用作记忆化表
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示「尚未计算」
        function<int(int, int)> dfs = [&](int i, int j) {  // 用 lambda 实现记忆化搜索；[&] 以引用捕获外部变量 n 与 f
            if (i >= n) {  // 越过最后一天（卖出后会跳到 i+2，所以 i 可能大于 n）
                return 0;  // 递归终点：没有剩余天数，收益为 0
            }  // 结束 if
            if (f[i][j] != -1) {  // 记忆化表里已经有答案
                return f[i][j];  // 直接查表返回
            }  // 结束 if
            int ans = dfs(i + 1, j);  // 选项一：今天不交易，保持同样的持股状态进入下一天
            if (j) {  // 当前处于持股状态（j 为 1）
                ans = max(ans, prices[i] + dfs(i + 2, 0));  // 卖掉：收入 prices[i]；明天是冷冻期，只能从 i+2 天以空仓状态继续
            } else {  // 当前处于空仓状态（j 为 0）
                ans = max(ans, -prices[i] + dfs(i + 1, 1));  // 买入：支出 prices[i]，明天以持股状态继续
            }  // 两种状态的 if-else 结束
            return f[i][j] = ans;  // 取较优决策，写入记忆化表并返回
        };  // lambda 结束
        return dfs(0, 0);  // 从第 0 天、空仓状态出发
    }  // maxProfit 结束
};  // Solution 类结束
