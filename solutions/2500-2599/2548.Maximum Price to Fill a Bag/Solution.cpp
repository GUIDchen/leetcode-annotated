// 题目：2548. 填满背包的最大价格（Maximum Price to Fill a Bag）
// 思路：贪心。物品允许按比例拆分，所以按单位重量价格从高到低排序，依次尽量装满；最后容量仍未用尽说明装不满，返回 -1。
// 时间复杂度：O(n log n)，由排序决定；空间复杂度：O(1)，除常数个变量外没有额外存储。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double maxPrice(vector<vector<int>>& items, int capacity) {  // items 的每个元素是 [price, weight]；capacity 是背包容量
        sort(items.begin(), items.end(), [&](const auto& a, const auto& b) { return a[1] * b[0] < a[0] * b[1]; });  // 贪心前置：按单位重量价格 price/weight 降序排序，交叉相乘比较可避免浮点误差
        double ans = 0;  // ans 累计已装入部分的价值
        for (auto& e : items) {  // 按单位价格从高到低依次尝试装袋
            int p = e[0], w = e[1];  // p 是该物品的价格，w 是该物品的重量
            int v = min(w, capacity);  // 本物品最多能装 min(重量, 剩余容量)
            ans += v * 1.0 / w * p;  // 按装入比例折算价值：v/w 就是装入比例
            capacity -= v;  // 扣掉本次占用的容量
        }
        return capacity > 0 ? -1 : ans;  // 容量没用完说明装不满，返回 -1；否则返回累计价值
    }
};