// 题目：1971. 寻找图中是否存在路径（Find if Path Exists in Graph）
// 思路：把无向边表建成邻接表，从 source 开始做 DFS，看能否访问到 destination。
// 时间复杂度：O(n + m)，每个点、每条边只访问一次；空间复杂度：O(n + m)，邻接表与访问标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {  // n：点数；edges：无向边表；source/destination：起点与终点
        vector<int> g[n];  // 邻接表：g[u] 保存与 u 直接相连的所有点
        vector<bool> vis(n);  // 访问标记数组，默认全为 false
        for (const auto& e : edges) {  // 遍历每条无向边
            int u = e[0], v = e[1];  // 边的两个端点
            g[u].push_back(v);  // u 的邻接表加入 v
            g[v].push_back(u);  // v 的邻接表加入 u（无向图要双向插入）
        }
        function<bool(int)> dfs = [&](int i) -> bool {  // 递归 DFS：判断从点 i 出发能否到达 destination
            if (i == destination) {  // 已经走到终点
                return true;  // 找到路径，返回成功
            }
            vis[i] = true;  // 标记当前点已访问，防止绕圈造成死循环
            for (int j : g[i]) {  // 枚举 i 的所有邻居
                if (!vis[j] && dfs(j)) {  // 邻居未访问且从它出发能到终点
                    return true;  // 提前返回成功，剪掉其余分支
                }
            }
            return false;  // 所有邻居都走不通
        };
        return dfs(source);  // 从起点开始搜索整张图
    }
};
