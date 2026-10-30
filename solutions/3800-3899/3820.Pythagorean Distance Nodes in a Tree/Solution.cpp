// 题目：3820. 树上的勾股距离节点（Pythagorean Distance Nodes in a Tree）
// 思路：树上没有环，任意两点的路径唯一。分别以 x、y、z 为起点做三次 BFS，得到每个节点到这三个起点的距离；把三个距离升序排序后判断是否满足勾股定理 a² + b² = c²，满足就把答案加一。
// 时间复杂度：O(n log n)，三次 BFS 各 O(n)，每个节点还有一次常数规模的排序；空间复杂度：O(n)，邻接表与三个距离数组。
class Solution {  // LeetCode 约定的题解类
private:  // 以下是内部实现细节
    vector<vector<int>> g;  // g 是树的邻接表
    int n;  // n 是节点总数
    const int inf = INT_MAX / 2;  // inf 表示「尚未访问」；取 INT_MAX / 2 是为了让 dist[u] + 1 不溢出

    vector<int> bfs(int i) {  // 以 i 为起点做 BFS，返回 i 到每个节点的最短距离
        vector<int> dist(n, inf);  // dist[v] 是起点到节点 v 的距离，初始化为无穷大表示未访问
        queue<int> q;  // q 是 BFS 队列，保证按距离从小到大的顺序扩展
        dist[i] = 0;  // 起点到自己的距离是 0
        q.push(i);  // 起点先入队
        while (!q.empty()) {  // 队列非空就继续向外扩展
            for (int k = q.size(); k > 0; --k) {  // 按当前层的元素个数整层处理，便于按层推进
                int u = q.front();  // 取出队首节点 u
                q.pop();  // 弹出队首
                for (int v : g[u]) {  // 遍历 u 的每个邻居 v
                    if (dist[v] > dist[u] + 1) {  // 只有尚未访问过的邻居（距离仍是 inf）才会满足该条件
                        dist[v] = dist[u] + 1;  // 松弛：更新 v 到起点的距离
                        q.push(v);  // v 入队，等待继续向外扩展
                    }
                }
            }
        }
        return dist;  // 返回起点到所有节点的距离数组
    }

public:  // 以下是对外提供的接口
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {  // n：节点数；edges：树的边；x、y、z：三个给定节点
        this->n = n;  // 记录节点数供 bfs 使用（与成员变量同名，需用 this 区分）
        g.assign(n, {});  // 邻接表初始化为 n 个空列表
        for (auto& e : edges) {  // 遍历每条边
            int u = e[0], v = e[1];  // 取出边的两个端点
            g[u].push_back(v);  // 无向边：登记 u -> v
            g[v].push_back(u);  // 无向边：登记 v -> u
        }

        vector<int> d1 = bfs(x);  // d1[i] 是节点 i 到 x 的距离
        vector<int> d2 = bfs(y);  // d2[i] 是节点 i 到 y 的距离
        vector<int> d3 = bfs(z);  // d3[i] 是节点 i 到 z 的距离

        int ans = 0;  // ans 统计满足勾股关系的节点个数
        for (int i = 0; i < n; ++i) {  // 逐个检查每个节点
            array<long long, 3> a = {  // 用 long long 保存三个距离，平方后不会溢出
                (long long) d1[i],  // 到 x 的距离
                (long long) d2[i],  // 到 y 的距离
                (long long) d3[i]};  // 到 z 的距离
            sort(a.begin(), a.end());  // 升序排序，这样 a[2] 就是斜边候选
            if (a[0] * a[0] + a[1] * a[1] == a[2] * a[2]) {  // 判断是否满足勾股定理 a² + b² = c²
                ++ans;  // 满足条件，计数加一
            }
        }
        return ans;  // 返回满足条件的节点个数
    }
};
