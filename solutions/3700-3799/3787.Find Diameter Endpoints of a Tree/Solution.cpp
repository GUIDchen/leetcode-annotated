// 题目：3787. 查找树的直径端点（Find Diameter Endpoints of a Tree）
// 核心思路：从任意点 BFS 得到直径端点 a，再从 a BFS 得到另一端点 b 与距离 dist1，最后从 b BFS 得到 dist2；直径长度为 dist1[b]，到 a 或到 b 距离等于直径的点即为某条直径的端点。
// 复杂度：时间 O(n)，三次 BFS 都是线性；空间 O(n)，邻接表加三次距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    string findSpecialNodes(int n, vector<vector<int>>& edges) {  // 返回长度为 n 的 01 串，第 i 位为 '1' 表示节点 i 是某条直径路径的端点
        vector<vector<int>> g(n);  // 邻接表建图
        for (auto& e : edges) {  // 逐条读入无向边
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a 的邻接表里加入 b
            g[b].push_back(a);  // b 的邻接表里加入 a
        }  // 建图结束

        auto bfs = [&](int start) -> pair<int, vector<int>> {  // lambda：从 start 出发做 BFS，返回 (最远点, 到各点的距离数组)
            vector<int> dist(n, -1);  // dist 初始化为 -1，兼作「未访问」标记
            dist[start] = 0;  // 起点到自身的距离为 0
            deque<int> q;  // BFS 用的双端队列
            q.push_back(start);  // 起点入队
            int far = start;  // far 记录已发现的离 start 最远的点
            while (!q.empty()) {  // 队列非空就继续扩展
                int u = q.front();  // 取出队首节点
                q.pop_front();  // 弹出队首
                if (dist[u] > dist[far]) {  // 距离更大则更新最远点
                    far = u;  // 更新最远点结束
                }  // 遍历 u 的所有邻居
                for (int v : g[u]) {  // 只从距离尚未确定的邻居继续扩展
                    if (dist[v] == -1) {  // 邻居到起点的距离为 u 的距离加一
                        dist[v] = dist[u] + 1;  // 邻居入队
                        q.push_back(v);  // 邻居判断结束
                    }  // 邻居遍历结束
                }  // BFS 主循环结束
            }  // 返回最远点与完整的距离数组
            return {far, dist};  // lambda 定义结束
        };
  // 第一次 BFS：从任意点 0 出发，找到直径的一个端点 a（_0 是无用的距离数组）
        auto [a, _0] = bfs(0);  // 第二次 BFS：从 a 出发找到另一端点 b，并得到 a 到各点的距离 dist1
        auto [b, dist1] = bfs(a);  // 第三次 BFS：从 b 出发得到 b 到各点的距离 dist2
        auto [_1, dist2] = bfs(b);  // 直径长度就是 a 到 b 的距离
        int d = dist1[b];
  // 结果串初始全为 '0'
        string ans(n, '0');  // 逐个节点判断它是否为某条直径的端点
        for (int i = 0; i < n; i++) {  // 到 a 或到 b 的距离等于直径长度，说明它是某条直径上的一端
            if (dist1[i] == d || dist2[i] == d) {  // 标记为特殊节点
                ans[i] = '1';  // 判断结束
            }  // 遍历结束
        }  // 返回 01 串
        return ans;  // 方法结束
    }
};  // 类定义结束
