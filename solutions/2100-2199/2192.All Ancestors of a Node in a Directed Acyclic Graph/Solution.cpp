// 题目：2192. 有向无环图中一个节点的所有祖先（All Ancestors of a Node in a Directed Acyclic Graph）
// 思路：以每个结点 s 为起点做一次 BFS，凡是从 s 能走到的结点 j，都把 s 记作 j 的一个祖先。
// 时间复杂度：O(n·(n+m))，需做 n 次 BFS；空间复杂度：O(n+m)，邻接表、队列与结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {  // n：结点个数；edges：描述有向边的二维数组
        vector<int> g[n];  // 邻接表：g[u] 保存 u 的所有直接后继结点
        for (auto& e : edges) {  // 遍历每一条有向边
            g[e[0]].push_back(e[1]);  // 建立 e[0] -> e[1] 的指向关系
        }  // for 结束
        vector<vector<int>> ans(n);  // 结果：ans[v] 记录 v 的全部祖先
        auto bfs = [&](int s) {  // 以 s 为祖先做一次 BFS
            queue<int> q;  // 队列：存放待扩展的结点
            q.push(s);  // 起点先入队
            bool vis[n];  // 访问标记数组，防止重复扩展同一个结点
            memset(vis, 0, sizeof(vis));  // 全部清零（即全部为 false）
            vis[s] = true;  // 起点标记为已访问
            while (q.size()) {  // 队列非空就继续扩展
                int i = q.front();  // 取队首结点
                q.pop();  // 队首出队
                for (int j : g[i]) {  // 枚举 i 的每个直接后继 j
                    if (!vis[j]) {  // j 本次还没有被访问过
                        vis[j] = true;  // 标记为已访问，避免重复入队
                        ans[j].push_back(s);  // s 能走到 j，说明 s 是 j 的祖先，记入结果
                        q.push(j);  // j 入队，继续向后扩展
                    }  // if 结束
                }  // for 结束
            }  // while 结束
        };  // lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 让每个结点依次当一次祖先
            bfs(i);  // 从 i 出发做 BFS
        }  // for 结束
        return ans;  // 返回每个结点的祖先列表；i 递增枚举，列表天然升序
    }  // 方法结束
};  // 类定义结束