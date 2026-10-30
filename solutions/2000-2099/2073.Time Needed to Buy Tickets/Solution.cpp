// 题目：2073. 买票需要的时间（Time Needed to Buy Tickets）
// 思路：第 k 个人买完 tickets[k] 张票之前，它前面（含自己）每人最多贡献 tickets[k] 张，它后面每人最多贡献 tickets[k] - 1 张，逐项取 min 累加。
// 时间复杂度：O(n)，只需遍历一遍数组；空间复杂度：O(1)，只用到常数个变量。
class Solution {  // 题解类：所有题解方法都写在这里
public:  // 方法对外可见（LeetCode 约定）
    int timeRequiredToBuy(vector<int>& tickets, int k) {  // tickets 是每个人的购票需求，k 是我们关注的人的下标
        int ans = 0;  // 累计卖出的票数，也就是经过的时间（每卖一张票用时 1 秒）
        for (int i = 0; i < tickets.size(); ++i) {  // 逐个统计每个人在第 k 个人买完票之前能买几张
            ans += min(tickets[i], i <= k ? tickets[k] : tickets[k] - 1);  // i <= k 的人最多买到 tickets[k] 张，i > k 的人最多只能买到 tickets[k] - 1 张
        }  // for 循环结束
        return ans;  // 返回总耗时
    }  // 方法结束
};  // 类定义结束