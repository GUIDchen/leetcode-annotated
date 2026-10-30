// 题目：1801. 积压订单中的订单总数（Number of Orders in the Backlog）
// 思路：卖单用价格小根堆、买单用价格大根堆；每来一笔订单先与对手盘按最优价格撮合，剩余数量入堆，最后统计两个堆里的剩余总量并取模。
// 时间复杂度：O(n log n)，每笔订单的撮合与入堆都是堆操作；空间复杂度：O(n)，堆中最多保存 n 笔订单。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {  // orders[i] = [price, amount, orderType]，type 为 0 表示买单、1 表示卖单
        using pii = pair<int, int>;  // 简化类型名：pair<价格, 数量>
        priority_queue<pii, vector<pii>, greater<pii>> sell;  // 卖单小根堆：堆顶是价格最低的卖单，最容易被买单吃掉
        priority_queue<pii> buy;  // 买单大根堆：堆顶是出价最高的买单，最容易被卖单吃掉
        for (auto& e : orders) {  // 按时间顺序处理每一笔新订单
            int p = e[0], a = e[1], t = e[2];  // p 为价格，a 为该订单剩余数量，t 为订单类型
            if (t == 0) {  // t == 0：这是买单，去找卖单撮合
                while (a && !sell.empty() && sell.top().first <= p) {  // 只要还有剩余量，且最便宜的卖单价格不高于出价，就继续成交
                    auto [x, y] = sell.top();  // 取出堆顶最便宜的卖单：x 价格、y 数量
                    sell.pop();  // 先弹出，下面按成交情况决定是否放回
                    if (a >= y) {  // 买单数量足以整笔吃掉这笔卖单
                        a -= y;  // 扣掉已成交的数量
                    } else {  // 否则买单不够，只能部分成交
                        sell.push({x, y - a});  // 卖单的剩余部分按原价放回堆中
                        a = 0;  // 买单被完全消耗
                    }
                }
                if (a) {  // 撮合完仍有剩余，说明这部分要挂进买单积压队列
                    buy.push({p, a});  // 按原价与剩余量存入买单堆
                }
            } else {  // 否则是卖单（t == 1），去找买单撮合
                while (a && !buy.empty() && buy.top().first >= p) {  // 只要还有剩余量，且最高买价不低于卖价，就继续成交
                    auto [x, y] = buy.top();  // 取出堆顶出价最高的买单：x 价格、y 数量
                    buy.pop();  // 先弹出，下面按成交情况决定是否放回
                    if (a >= y) {  // 卖单数量足以整笔吃掉这笔买单
                        a -= y;  // 扣掉已成交的数量
                    } else {  // 否则卖单不够，只能部分成交
                        buy.push({x, y - a});  // 买单的剩余部分按原价放回堆中
                        a = 0;  // 卖单被完全消耗
                    }
                }
                if (a) {  // 卖单仍有剩余，挂进卖单积压队列
                    sell.push({p, a});  // 按原价与剩余量存入卖单堆
                }
            }
        }
// 统计阶段：两个堆里剩余的数量之和就是积压订单数
        long ans = 0;  // 积压订单总数可能很大，用 long 累加避免溢出
        while (!buy.empty()) {  // 累加所有积压买单的数量
            ans += buy.top().second;  // 把堆顶数量加到答案里
            buy.pop();  // 弹出已统计过的堆顶
        }
        while (!sell.empty()) {  // 累加所有积压卖单的数量
            ans += sell.top().second;  // 把堆顶数量加到答案里
            sell.pop();  // 弹出已统计过的堆顶
        }
        const int mod = 1e9 + 7;  // 题目要求对 1e9+7 取模
        return ans % mod;  // 返回积压订单总数
    }
};