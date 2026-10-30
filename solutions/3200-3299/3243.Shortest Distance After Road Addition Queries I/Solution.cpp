// 题目：3243. 新增道路查询后的最短距离 I（Shortest Distance After Road Addition Queries I）
// 思路：初始图是链 0->1->...->(n-1)，每次加边后用 BFS 重新求 0 到 n-1 的最短距离。
// 时间复杂度：O(q·(n+m))，每次查询跑一遍 BFS；空间复杂度：O(n+m)，邻接表、队列与访问数组。
class Solution {  // // LeetCode 约定的题解类
public:  // // 题解方法对外可见
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {  // // n 是城市数，queries 是依次新增的有向道路，返回每加一条边后 0 到 n-1 的最短距离
        vector<int> g[n];  // // 邻接表：g[i] 保存从城市 i 出发能直接到达的城市
        for (int i = 0; i < n - 1; ++i) {  // // 先把题目给定的初始道路逐条建好
            g[i].push_back(i + 1);  // // 初始图中 i 只能直接走到 i+1
        }  // // 初始边建完，循环结束
        auto bfs = [&](int i) -> int {  // // 定义 BFS 闭包：从起点 i 求到 n-1 的最短边数；[&] 按引用捕获外部的 g 与 n
            queue<int> q{{i}};  // // 队列里只放起点，BFS 从起点开始分层扩展
            vector<bool> vis(n);  // // 访问标记数组，防止同一个点被重复入队
            vis[i] = true;  // // 起点先标记为已访问
            for (int d = 0;; ++d) {  // // d 表示当前已经走过的边数，每扩一层就加一
                for (int k = q.size(); k; --k) {  // // 一次只处理当前队列中的一整层节点，保证这一层距离都是 d
                    int u = q.front();  // // 取出队首节点 u
                    q.pop();  // // 弹出队首，继续处理该层剩余节点
                    if (u == n - 1) {  // // 如果已经到达终点 n-1
                        return d;  // // 当前层数就是最短距离，直接返回
                    }  // // 到达终点的分支结束
                    for (int v : g[u]) {  // // 枚举 u 的所有出边
                        if (!vis[v]) {  // // 只把还没访问过的邻居加入队列
                            vis[v] = true;  // // 入队前先打上访问标记，避免同一节点重复入队
                            q.push(v);  // // 邻居入队，留到下一层扩展
                        }  // // 未访问判断结束
                    }  // // 出边遍历结束
                }  // // 当前这一层处理完毕
            }  // // 外层无限循环结束（实际由内部的 return 退出）
        };  // // BFS lambda 定义结束
        vector<int> ans;  // // ans 保存每次加边后的最短距离
        for (const auto& q : queries) {  // // 依次处理每条新增道路
            g[q[0]].push_back(q[1]);  // // 把有向边 q[0] -> q[1] 加入邻接表
            ans.push_back(bfs(0));  // // 加边后重新从 0 号城市跑一次 BFS，并把结果记入答案
        }  // // 查询循环结束
        return ans;  // // 返回所有查询的答案
    }  // // 方法结束
};  // // 类结束
