// 题目：123. 买卖股票的最佳时机 III（Best Time to Buy and Sell Stock III）
// 思路：状态机 DP，f1/f2/f3/f4 分别表示「第一次买入后、第一次卖出后、第二次买入后、第二次卖出后」的最大收益，逐日滚动更新。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只有四个状态变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProfit(vector<int>& prices) {  // prices：每天的价格序列，最多允许两笔完整交易
        int f1 = -prices[0], f2 = 0, f3 = -prices[0], f4 = 0;  // 第一天只能买入，故两个买入态初值是 -prices[0]，两个卖出态（未交易）初值是 0
        for (int i = 1; i < prices.size(); ++i) {  // 从第二天开始逐日推进四个状态
            f1 = max(f1, -prices[i]);  // 第一次买入：要么保持此前更低成本的持仓，要么今天才第一次买入
            f2 = max(f2, f1 + prices[i]);  // 第一次卖出：要么此前已卖，要么用 f1 的成本在今天兑现
            f3 = max(f3, f2 - prices[i]);  // 第二次买入：用第一笔交易的收益 f2 作为本金在今天买入
            f4 = max(f4, f3 + prices[i]);  // 第二次卖出：把第二次买入的成本 f3 在今天兑现
        }  // 一天的更新全部完成
        return f4;  // f4 就是最多两笔交易（也可以少于两笔）后的最大收益
    }  // maxProfit 结束
};