// 题目：2642. 设计可以求最短路径的图类（Design Graph With Shortest Path Calculator）
// 思路：邻接矩阵存有向边，最短路用朴素 Dijkstra：每轮选出未访问的最近点，再用它松弛所有出边。
// 时间复杂度：构造 O(n^2)，加边 O(1)，单次最短路 O(n^2)；空间复杂度：O(n^2)，邻接矩阵。
class Graph {  // 题目要求实现的图类
public:
    Graph(int n, vector<vector<int>>& edges) {  // n：节点数；edges：初始有向边 [from, to, cost]
        this->n = n;  // 保存节点数，供后面的成员函数使用
        g = vector<vector<int>>(n, vector<int>(n, inf));  // 邻接矩阵初始化为「无穷大」，表示暂不可达
        for (auto& e : edges) {  // 逐条写入初始边
            int f = e[0], t = e[1], c = e[2];  // 拆出起点、终点、边权
            g[f][t] = c;  // 有向边写入邻接矩阵
        }
    }

    void addEdge(vector<int> edge) {  // 动态增加一条有向边
        int f = edge[0], t = edge[1], c = edge[2];  // 拆出起点、终点、边权
        g[f][t] = c;  // 直接写入矩阵，题目保证这些边不会相互冲突
    }

    int shortestPath(int node1, int node2) {  // 求 node1 到 node2 的最短距离，不可达返回 -1
        vector<bool> vis(n);  // vis[j] 标记节点 j 的最短距离是否已经确定
        vector<int> dist(n, inf);  // dist[j] 是 node1 到 j 的当前最短距离估计
        dist[node1] = 0;  // 起点到自身的距离为 0
        for (int i = 0; i < n; ++i) {  // 最多 n 轮，每轮确定一个节点
            int t = -1;  // t 记录本轮要确定的节点，-1 表示还没选出来
            for (int j = 0; j < n; ++j) {  // 在未确定的节点里找距离最小的那个
                if (!vis[j] && (t == -1 || dist[t] > dist[j])) {  // j 未确定，且比当前候选更近
                    t = j;  // 更新候选节点
                }
            }
            vis[t] = true;  // 最近的节点距离已经可以确定，标记为已访问
            for (int j = 0; j < n; ++j) {  // 用 t 去松弛它所有的出边
                dist[j] = min(dist[j], dist[t] + g[t][j]);  // 经 t 中转是否更短，取较小值
            }
        }
        return dist[node2] >= inf ? -1 : dist[node2];  // 仍是无穷大说明不可达，按题目要求返回 -1
    }

private:
    vector<vector<int>> g;  // 邻接矩阵：g[u][v] 表示 u 到 v 的有向边权
    int n;  // 节点个数
    const int inf = 1 << 29;  // 足够大的「无穷」，与真实距离相加也不会溢出 int
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */