// 题目：2737. 找到最近的标记节点（Find the Closest Marked Node）
// 思路：在邻接矩阵上跑朴素 Dijkstra 求出起点 s 到每个点的最短路，再在所有标记节点中取距离最小值；全部不可达则返回 -1。
// 时间复杂度：O(n^2 + m)，Dijkstra 两层循环 n^2，加读入 m 条边；空间复杂度：O(n^2)，邻接矩阵占主导。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {  // n 是节点数，edges 是有向带权边，s 是起点，marked 是标记节点列表
        const int inf = 1 << 29;  // 取 2^29 作为无穷大：足够大，且两个 inf 相加也不会溢出 int
        vector<vector<int>> g(n, vector<int>(n, inf));  // 邻接矩阵，初始全是 inf 表示暂时没有边
        vector<int> dist(n, inf);  // dist[i] 表示从起点 s 到节点 i 的最短距离，先整体置为 inf
        dist[s] = 0;  // 起点到自身的距离是 0
        vector<bool> vis(n);  // vis[i] 记录节点 i 的最短距离是否已经确定，默认全为 false
        for (auto& e : edges) {  // 逐条读入有向边
            int u = e[0], v = e[1], w = e[2];  // 拆出边的起点 u、终点 v 与权值 w
            g[u][v] = min(g[u][v], w);  // 同一对节点间可能有多条边，只保留最小的那条
        }  // 读边循环结束
        for (int i = 0; i < n; ++i) {  // Dijkstra 主循环：每次确定一个节点的最短距离，共 n 轮
            int t = -1;  // t 用来记录本轮距离最小且尚未确定的节点，-1 表示还没选到
            for (int j = 0; j < n; ++j) {  // 在未确定的节点里线性扫描找 dist 最小的那个
                if (!vis[j] && (t == -1 || dist[t] > dist[j])) {  // j 未确定，并且（还没选过 or 比当前候选 t 更近）
                    t = j;  // 更新本轮选中的节点
                }  // if 判空结束
            }  // 内层选择循环结束
            vis[t] = true;  // 把 t 的最短距离标记为已确定，之后不再更新它
            for (int j = 0; j < n; ++j) {  // 用 t 作为中转去松弛所有节点
                dist[j] = min(dist[j], dist[t] + g[t][j]);  // 若经过 t 再到 j 更近，就更新 dist[j]；g[t][j] 为 inf 时相加也不会溢出
            }  // 松弛循环结束
        }  // Dijkstra 主循环结束
        int ans = inf;  // 答案取所有标记节点中的最小距离，先置为 inf
        for (int i : marked) {  // 遍历每个标记节点
            ans = min(ans, dist[i]);  // 保留其中离起点最近的距离
        }  // 标记节点循环结束
        return ans >= inf ? -1 : ans;  // 若最小距离仍是 inf 说明全都不可达，返回 -1，否则返回该距离
    }  // 方法体结束
};  // 类定义结束