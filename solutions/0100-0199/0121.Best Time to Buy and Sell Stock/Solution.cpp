// 题目：121. 买卖股票的最佳时机（Best Time to Buy and Sell Stock）
// 思路：一次遍历，mi 维护遍历到目前为止的历史最低价，每天用「今天价格 - 历史最低价」更新最大利润，然后再用今天价格更新最低价。
// 时间复杂度：O(n)，每个价格只访问一次；空间复杂度：O(1)，只用了两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProfit(vector<int>& prices) {  // prices 是每日股价，返回一次买入再卖出能获得的最大利润
        int ans = 0, mi = prices[0];  // ans 记录最大利润（不交易就是 0）；mi 记录历史最低价，先取第一天的价格
        for (int& v : prices) {  // 按时间顺序遍历每一天的价格，用引用避免拷贝
            ans = max(ans, v - mi);  // 假设今天卖出、在历史最低点买入，尝试更新答案
            mi = min(mi, v);  // 再把今天价格并入历史最低价，供后面的日子使用（放在后面保证不会自己减自己）
        }
        return ans;  // 返回最大利润
    }
};  // 类定义结束