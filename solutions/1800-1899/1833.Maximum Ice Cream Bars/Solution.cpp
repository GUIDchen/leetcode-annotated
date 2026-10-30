// 题目：1833. 雪糕的最大数量（Maximum Ice Cream Bars）
// 思路：贪心，先按价格升序排序，再从最便宜的雪糕开始买，直到钱不够为止。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(log n)，排序递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxIceCream(vector<int>& costs, int coins) {  // costs：各雪糕的价格；coins：手里的钱；返回最多能买的雪糕数量
        sort(costs.begin(), costs.end());  // 按价格升序排序，优先买便宜的自然买得最多
        int n = costs.size();  // 雪糕总数
        for (int i = 0; i < n; ++i) {  // 从便宜到贵依次尝试购买
            if (coins < costs[i]) return i;  // 钱不够买当前这支，说明最多只能买前 i 支
            coins -= costs[i];  // 买下当前雪糕，扣除花费
        }  // 循环结束
        return n;  // 钱够买完全部雪糕
    }  // 方法结束
};  // 类定义结束