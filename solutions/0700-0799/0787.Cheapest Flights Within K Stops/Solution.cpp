// 题目：787. K 站中转内最便宜的航班（Cheapest Flights Within K Stops）
// 思路：边数受限的 Bellman-Ford；每轮用上一轮快照 backup 只多放松一条边，迭代 k+1 轮即最多 k 站中转。
// 时间复杂度：O(k·m)，m 为航班数；空间复杂度：O(n)，距离数组与快照数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {  // n 个城市，flights 每项为 [起点, 终点, 价格]，求 src 到 dst 最多 k 站中转的最低价
        const int inf = 0x3f3f3f3f;  // 足够大的「不可达」标记，再加一条边的价格也不会溢出 int
        vector<int> dist(n, inf);  // dist[v]：本轮结束后到达 v 的最小花费
        vector<int> backup;  // 上一轮 dist 的快照，保证每轮只多走一条边
        dist[src] = 0;  // 起点到自身的花费是 0
        for (int i = 0; i < k + 1; ++i) {  // 最多 k 站中转，等价于最多走 k+1 条边
            backup = dist;  // 冻结上一轮结果：本轮松弛只读快照，避免一轮内连续走多条边而突破中转限制
            for (auto& e : flights) {  // 枚举所有航班边
                int f = e[0], t = e[1], p = e[2];  // 拆出这条边的起点 f、终点 t 与价格 p
                dist[t] = min(dist[t], backup[f] + p);  // 用「上一轮到达 f 的花费 + 这条边价格」尝试更新 t 的最小花费
            }  // 内层边循环结束
        }  // 轮次循环结束
        return dist[dst] == inf ? -1 : dist[dst];  // 仍为 inf 说明不可达返回 -1，否则返回最小花费
    }  // 方法结束
};  // 题解类结束