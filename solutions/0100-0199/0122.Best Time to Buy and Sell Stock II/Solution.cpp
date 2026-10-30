// 题目：122. 买卖股票的最佳时机 II（Best Time to Buy and Sell Stock II）
// 思路：看相邻两天的差分，只要后一天比前一天贵就把这段差价吃掉，等价于无限次低买高卖。
// 时间复杂度：O(n)，只扫描一遍价格数组；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProfit(vector<int>& prices) {  // prices：每天的价格序列，返回能获得的最大利润
        int ans = 0;  // 累计利润，初始为 0 表示也可以一次都不交易
        for (int i = 1; i < prices.size(); ++i) ans += max(0, prices[i] - prices[i - 1]);  // max(0, 差价) 把下跌的那天当作不操作，所有上涨段累加起来就是最优解
        return ans;  // 返回最大总利润
    }  // maxProfit 结束
};