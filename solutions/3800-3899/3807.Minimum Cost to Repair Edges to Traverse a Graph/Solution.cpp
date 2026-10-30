// 3807. Minimum Cost to Repair Edges to Traverse a Graph | 修复边以遍历图的最小成本
// 核心思路：把边按修复代价升序排序，二分“只允许使用前 idx+1 条最便宜的边”的前缀，用 BFS 层数判断 0 到 n-1 的最短路是否不超过 k 条边；答案就是最小可行前缀末端那条边的代价。
// 复杂度：时间 O(m log m + (n + m) log m)（排序 + log m 次 BFS）；空间 O(n + m)。
class Solution {  // 定义题解类
public:  // 公有接口
    int minCost(int n, vector<vector<int>>& edges, int k) {  // 返回从 0 到 n-1、且路径边数不超过 k 时的最小修复代价
        sort(edges.begin(), edges.end(),  // 把边按修复代价升序排序，答案一定落在某条已排序边的代价上
            [](const vector<int>& a, const vector<int>& b) {  // 比较器：只看第 3 个字段（代价）
                return a[2] < b[2];  // 代价小的边排在前面
            });  // 排序结束

        auto check = [&](int idx) -> bool {  // check(idx)：只使用前 idx+1 条最便宜的边，判断能否在不超过 k 条边内走到 n-1
            vector<vector<int>> g(n);  // 为本次判定重建邻接表，n 个空列表
            for (int i = 0; i <= idx; ++i) {  // 枚举前缀中所有可用的边
                int u = edges[i][0], v = edges[i][1];  // 取出第 i 条边的两个端点
                g[u].push_back(v);  // 加入有向边 u -> v
                g[v].push_back(u);  // 加入有向边 v -> u（无向图双向建边）
            }  // 邻接表构建完毕

            vector<int> q;  // BFS 的当前层节点队列
            q.push_back(0);  // 起点 0 入队
            vector<char> vis(n, 0);  // 访问标记数组，0 表示未访问
            vis[0] = 1;  // 起点标记为已访问

            int dist = 0;  // dist 表示当前层号，也就是已走过的边数
            while (!q.empty()) {  // 按层推进 BFS
                vector<int> nq;  // 收集下一层的节点
                for (int u : q) {  // 遍历当前层的每个节点
                    if (u == n - 1) {  // 到达终点
                        return dist <= k;  // 边数不超过 k 才可行
                    }  // 结束终点判断
                    for (int v : g[u]) {  // 扩展 u 的邻居
                        if (!vis[v]) {  // 邻居尚未访问
                            vis[v] = 1;  // 标记为已访问，防止重复入队
                            nq.push_back(v);  // 放进下一层
                        }  // 结束未访问判断
                    }  // 结束邻居遍历
                }  // 当前层遍历完毕
                q.swap(nq);  // 队列切换到下一层
                ++dist;  // 层号（边数）加一
            }  // BFS 结束仍未到达终点
            return false;  // 不可达或步数超过 k，判定失败
        };  // check lambda 定义结束

        int m = edges.size();  // 边的总条数
        int l = 0, r = m - 1;  // 二分区间：最小可行前缀下标 [l, r]
        while (l < r) {  // 二分查找最小的可行下标
            int mid = (l + r) >> 1;  // 取中点
            if (check(mid)) {  // 只用前 mid+1 条边就已经可行
                r = mid;  // 答案可能更小，收缩右端
            } else {  // 该前缀不可行
                l = mid + 1;  // 必须放开更多（更贵的）边
            }  // 结束 if/else 分支
        }  // 二分结束，l 即最小可行下标
        return check(l) ? edges[l][2] : -1;  // 可行时第 l 条边正是该前缀中最贵的一条，其代价就是答案；否则返回 -1
    }  // 方法结束
};  // 类定义结束
