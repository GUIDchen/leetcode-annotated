// 题目：2093. 前往目标城市的最小费用（Minimum Cost to Reach City With Discounts）
// 思路：把「已用折扣次数」并入状态做分层 Dijkstra，每条边扩展出「原价」与「半价且次数 +1」两个后继。
// 时间复杂度：O(m·d·log(m·d))，d = discounts，每个状态至多入堆一次；空间复杂度：O(n·d)，dist 表与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {  // n：城市数；highways：{a, b, c} 公路；discounts：可用折扣次数上限
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[u] 存 {相邻城市, 过路费}
        for (auto& e : highways) {  // 逐条读取公路
            int a = e[0], b = e[1], c = e[2];  // 拆出两个端点与过路费
            g[a].push_back({b, c});  // 建 a -> b 的边
            g[b].push_back({a, c});  // 公路是无向的，再建 b -> a 的边
        }
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;  // 小根堆，元素为 (已花费用, 城市, 已用折扣次数)
        q.push({0, 0, 0});  // 起点是 0 号城市，费用 0，尚未使用折扣
        vector<vector<int>> dist(n, vector<int>(discounts + 1, INT_MAX));  // dist[i][k]：用掉 k 次折扣到达城市 i 的最小费用，初始为无穷大
        while (!q.empty()) {  // Dijkstra 主循环
            auto [cost, i, k] = q.top();  // 取出当前费用最小的状态
            q.pop();  // 出堆
            if (k > discounts || dist[i][k] <= cost) continue;  // 折扣次数超限，或该状态已有更优解时直接跳过
            if (i == n - 1) return cost;  // 第一次弹出终点即为最小费用（最短路性质）
            dist[i][k] = cost;  // 确认该状态的最优费用
            for (auto [j, v] : g[i]) {  // 枚举从 i 出发的每条公路
                q.push({cost + v, j, k});  // 不使用折扣：正常付费，次数不变
                q.push({cost + v / 2, j, k + 1});  // 使用一次折扣：费用减半（下取整），次数加一
            }
        }
        return -1;  // 堆空仍未到达终点，说明不可达
    }
};