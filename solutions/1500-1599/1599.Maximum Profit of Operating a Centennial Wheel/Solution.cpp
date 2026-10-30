// 题目：1599. 经营摩天轮的最大利润（Maximum Profit of Operating a Centennial Wheel）
// 思路：按轮模拟，累计等待人数、每轮最多上 4 人，维护累计利润并在出现更高利润时记录轮数。
// 时间复杂度：O(n)，每轮处理一次到达数据；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {  // customers[i] 是第 i 轮到达人数，boardingCost 每人票价，runningCost 每轮运营成本
        int ans = -1;  // 达到最大利润所需的最少轮数，-1 表示怎么运营都不赚钱
        int mx = 0, t = 0;  // mx 记录历史最大利润，t 记录当前累计利润
        int wait = 0, i = 0;  // wait 是排队等待人数，i 是已经读到的到达轮次
        while (wait || i < customers.size()) {  // 还有人排队或在等后续顾客到达，就继续转
            wait += i < customers.size() ? customers[i] : 0;  // 本轮新到达的顾客加入等待队列
            int up = min(4, wait);  // 摩天轮一次最多上 4 人
            wait -= up;  // 上车的人从等待队列里移除
            ++i;  // 转完一轮，轮数加一
            t += up * boardingCost - runningCost;  // 本轮收入减去运营成本，累加到总利润
            if (t > mx) {  // 只有出现更高的利润才更新答案
                mx = t;  // 记录新的最大利润
                ans = i;  // 记录达到该利润的最少轮数
            }  // 更新判断结束
        }  // 模拟循环结束
        return ans;  // 返回最少轮数（从未盈利则为 -1）
    }  // 方法结束
};  // 类结束