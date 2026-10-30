// 题目：2359. 找到离给定两个节点最近的节点（Find Closest Node to Given Two Nodes）
// 思路：每个点出度至多为 1，从两个起点各做一次 BFS 求出到所有点的距离，再取 max(d1[i], d2[i]) 最小的 i（下标记最小）。
// 时间复杂度：O(n)，两次 BFS 各遍历一遍点与边；空间复杂度：O(n)，邻接表与两个距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {  // edges：每个点唯一的出边，-1 表示没有出边；node1、node2 为两个起点
        int n = edges.size();  // n 为节点总数
        vector<vector<int>> g(n);  // 邻接表，g[i] 存放从 i 出发能到达的点
        for (int i = 0; i < n; ++i) {  // 遍历每个点建立有向边
            if (edges[i] != -1) {  // 该点存在出边时才建边
                g[i].push_back(edges[i]);  // 把唯一的出边加入邻接表
            }  // 出边判断结束
        }  // 建图结束
        const int inf = 1 << 30;  // 用一个足够大的数表示“不可达”
        using pii = pair<int, int>;  // 给 pair<int, int> 起别名，便于阅读
        auto f = [&](int i) {  // lambda：从起点 i 出发，BFS 求出到每个点的最短距离
            vector<int> dist(n, inf);  // 距离数组，初始全部视为不可达
            dist[i] = 0;  // 起点到自己的距离为 0
            queue<int> q{{i}};  // 队列用起点初始化（花括号构造）
            while (!q.empty()) {  // 队列不空就继续扩展
                i = q.front();  // 取出队首节点
                q.pop();  // 弹出队首，避免重复处理
                for (int j : g[i]) {  // 遍历当前节点的所有出边
                    if (dist[j] == inf) {  // 目标点还没被访问过
                        dist[j] = dist[i] + 1;  // 最优性：BFS 首次到达即最短距离
                        q.push(j);  // 入队，等待继续向外扩展
                    }  // 未访问判断结束
                }  // 出边遍历结束
            }  // 队列循环结束
            return dist;  // 返回从起点 i 出发到所有点的距离数组
        };  // lambda 定义结束
        vector<int> d1 = f(node1);  // node1 到每个点的最短距离
        vector<int> d2 = f(node2);  // node2 到每个点的最短距离
        int ans = -1, d = inf;  // ans 记录答案节点，d 记录当前最小的“较大距离”，inf 也顺带表示尚无可行点
        for (int i = 0; i < n; ++i) {  // 按下标从小到大扫描所有点，天然满足“距离相同取下标最小”的要求
            int t = max(d1[i], d2[i]);  // 该点到两个起点的距离取较大者
            if (t < d) {  // 严格小于才更新，保证等距时保留下标更小的点
                d = t;  // 更新当前最优的较大距离
                ans = i;  // 记录取得该最优值的节点
            }  // 更优判断结束
        }  // 扫描结束
        return ans;  // 没有两个起点都可到达的点时 ans 保持 -1
    }  // 方法结束
};  // 类定义结束