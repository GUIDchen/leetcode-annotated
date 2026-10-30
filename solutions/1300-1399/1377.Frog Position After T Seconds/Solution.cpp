// 题目：1377. T 秒后青蛙的位置（Frog Position After T Seconds）
// 思路：从结点 1 开始按层 BFS，每个结点把概率按可选邻居数平分给未访问的邻居；若在第 t 秒到达 target 且无路可走，就返回该概率，否则为 0。
// 时间复杂度：O(n)，每个结点至多入队一次；空间复杂度：O(n)，邻接表、访问数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {  // n 为结点数，edges 为无向边，t 为秒数，target 为目标结点
        vector<vector<int>> g(n + 1);  // 邻接表：下标 1..n 存每个结点的邻居（0 号下标空置）
        for (auto& e : edges) {  // 逐条边建无向图，每条边正反各连一次
            int u = e[0], v = e[1];  // 取出这条边的两个端点
            g[u].push_back(v);  // 从 u 连到 v
            g[v].push_back(u);  // 从 v 连到 u
        }  // 建图结束
        queue<pair<int, double>> q{{{1, 1.0}}};  // 队列元素是「当前结点, 青蛙到达该结点的概率」，初始在结点 1，概率为 1
        bool vis[n + 1];  // 访问标记数组，避免沿着树往回走
        memset(vis, false, sizeof(vis));  // 全部初始化为未访问
        vis[1] = true;  // 起点 1 标记为已访问
        for (; q.size() && t >= 0; --t) {  // 按层推进，t 秒耗尽或队列为空时停止，每轮代表一秒
            for (int k = q.size(); k; --k) {  // 只处理当前这一层的结点，循环中新入队的属于下一秒
                auto [u, p] = q.front();  // 取出队首的结点与到达概率
                q.pop();  // 弹出队首元素
                int cnt = g[u].size() - (u != 1);  // 可选邻居数：根结点 1 没有父结点，其余结点要减去回父结点的那条边
                if (u == target) {  // 到达目标结点
                    return cnt * t == 0 ? p : 0;  // 已无路可走（cnt*t == 0，即叶子或时间耗尽）就停在原地，否则下去后离开，概率为 0
                }  // 目标结点判断结束
                for (int v : g[u]) {  // 枚举当前结点的所有邻居
                    if (!vis[v]) {  // 只走没有访问过的结点，保证沿树向下推进
                        vis[v] = true;  // 标记为已访问，防止被再次入队
                        q.push({v, p / cnt});  // 以 cnt 分之一的条件概率进入该邻居，概率相乘
                    }  // 邻居判断结束
                }  // 邻居遍历结束
            }  // 当前层处理结束
        }  // 按层循环结束
        return 0;  // t 秒内没有停在 target 上，概率为 0
    }  // 方法结束
};  // 类定义结束