// 题目：2662. 前往目标的最小代价（Minimum Cost of a Path With Special Roads）
// 核心思路：在「起点 + 所有特殊道路出口」这些关键点上做 Dijkstra 式优先队列松弛，每次从当前点走到目标作为候选答案，再尝试经由每条特殊道路继续扩展；同时用距离下界剪掉重复状态。
// 时间复杂度：O(E log E)，E 为弹出的状态数（受特殊道路条数限制）；空间复杂度：O(E)，优先队列与访问集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {  // start：起点坐标；target：终点坐标；specialRoads：每条特殊道路 {x1,y1,x2,y2,cost}
        auto dist = [](int x1, int y1, int x2, int y2) {  // lambda：曼哈顿距离，也就是两个坐标之间的普通行走代价
            return abs(x1 - x2) + abs(y1 - y2);  // 曼哈顿距离公式：横纵坐标差取绝对值再相加
        };  // lambda 定义结束
        int ans = 1 << 30;  // 答案初值取一个足够大的数（2^30），后面会被逐步收紧
        int n = 1e6;  // 哈希用的行宽基数，取 1e6 保证不同坐标拼成的键不冲突
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;  // 小根堆：按当前累计代价升序弹出状态
        pq.push({0, start[0], start[1]});  // 起点状态入堆，从起点出发的代价为 0
        unordered_set<long long> vis;  // 访问集合：记录已经确定过最优代价的坐标（用 long long 编码的键）
        while (!pq.empty()) {  // 开始 Dijkstra 主循环：堆非空就继续扩展
            auto [d, x, y] = pq.top();  // 弹出当前累计代价最小的状态（结构化绑定取代价 d 与坐标 x、y）
            pq.pop();  // 把弹出的元素从堆中删除
            long long k = 1LL * x * n + y;  // 把坐标压成一个 long long 作为访问集合的键，避免自定义哈希
            if (vis.count(k)) {  // 该坐标之前已经以更优（或相等）的代价处理过
                continue;  // 重复状态直接跳过，防止无效扩展
            }  // if 分支结束
            vis.insert(k);  // 标记该坐标已处理，保证每个坐标只扩展一次
            ans = min(ans, d + dist(x, y, target[0], target[1]));  // 从当前点直接走到终点，用这条路径的代价更新答案
            for (auto& r : specialRoads) {  // 枚举每一条特殊道路，尝试从当前点绕行过去
                int x1 = r[0], y1 = r[1], x2 = r[2], y2 = r[3], cost = r[4];  // 取出该道路的起点 (x1,y1)、终点 (x2,y2) 以及走完它的固定花费 cost
                pq.push({d + dist(x, y, x1, y1) + cost, x2, y2});  // 代价 = 走到道路入口的曼哈顿距离 + 道路花费，入堆候选状态为道路出口 (x2,y2)
            }  // 特殊道路循环结束
        }  // 主循环结束：所有可达的关键状态都处理完毕
        return ans;  // 返回记录到的最小代价
    }  // 方法结束
};  // 类定义结束（文件末尾无换行，按原样保留）