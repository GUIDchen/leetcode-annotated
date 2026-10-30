// 题目：2706. 购买两块巧克力（Buy Two Chocolates）
// 思路：先对价格升序排序，最便宜的两块之和就是最低花费；若超过 money 就一块也不买，原样返回 money。
// 时间复杂度：O(n log n)，排序是瓶颈；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int buyChoco(vector<int>& prices, int money) {  // prices：每块巧克力的价格；money：你手里拥有的钱
        sort(prices.begin(), prices.end());  // 升序排序，让最便宜的两块排到数组最前面
        int cost = prices[0] + prices[1];  // 买两块巧克力的最低总花费
        return money < cost ? money : money - cost;  // 花得起就返回剩余的钱，花不起就返回原来的 money
    }
};