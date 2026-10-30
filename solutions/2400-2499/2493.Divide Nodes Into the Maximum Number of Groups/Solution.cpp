// 题目：2493. 将节点分成尽可能多的组（Divide Nodes Into the Maximum Number of Groups）
// 思路：先用 BFS 判二分图（相邻层差必须为 1），再对每个连通块取「任一点为源 BFS 的最大层数」，按最小编号根汇总求和。
// 时间复杂度：O(n(n+m))，每个点各做一次 BFS；空间复杂度：O(n+m)，邻接表、dist 数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int magnificentSets(int n, vector<vector<int>>& edges) {  // n 是节点数（编号 1..n），edges 是边的端点列表
        vector<int> g[n];  // 邻接表，节点编号统一转成 0..n-1
        for (auto& e : edges) {  // 遍历每条无向边建图
            int a = e[0] - 1, b = e[1] - 1;  // 输入编号从 1 开始，减 1 转成 0 起下标
            g[a].push_back(b);  // a 到 b 加一条边
            g[b].push_back(a);  // b 到 a 再加一条，构成无向图
        }  // 建图完成
        vector<int> d(n);  // 按连通块根记录该块能达到的最大组数，缺省为 0
        for (int i = 0; i < n; ++i) {  // 以每个点作为 BFS 源，求它所在连通块的候选组数
            queue<int> q{{i}};  // BFS 队列，初始只有源点 i
            vector<int> dist(n);  // 本轮 BFS 的层次数组，0 表示未访问
            dist[i] = 1;  // 源点放在第 1 组
            int mx = 1;  // 当前 BFS 能达到的最大层数
            int root = i;  // 记录本轮访问过的最小编号，作为连通块代表
            while (q.size()) {  // 队列非空时继续 BFS
                int a = q.front();  // 取出队首节点
                q.pop();  // 弹出队首
                root = min(root, a);  // 连通块代表取访问过的点中最小的编号
                for (int b : g[a]) {  // 遍历 a 的每个邻居
                    if (dist[b] == 0) {  // 邻居还没分层
                        dist[b] = dist[a] + 1;  // 相邻节点的组号必须相差 1
                        mx = max(mx, dist[b]);  // 更新当前 BFS 的最大层数
                        q.push(b);  // 邻居入队继续扩展
                    } else if (abs(dist[b] - dist[a]) != 1) {  // 已分层但层差不为 1，说明出现奇环，无法按要求分组
                        return -1;  // 不是二分图，直接返回 -1
                    }  // 该邻居处理完毕
                }  // a 的邻居遍历结束
            }  // 队列已清空，本轮 BFS 结束
            d[root] = max(d[root], mx);  // 同一连通块取最大的 BFS 层数作为该块贡献
        }  // 所有点都作为源试过
        return accumulate(d.begin(), d.end(), 0);  // 各连通块贡献之和即最多组数
    }  // 方法结束
};  // 类定义结束