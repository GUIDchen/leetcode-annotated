// 题目：847. 访问所有节点的最短路径（Shortest Path Visiting All Nodes）
// 思路：状态压缩 BFS，状态是（当前节点, 已访问节点集合的二进制掩码），按步数分层扩展直到掩码覆盖全部节点。
// 时间复杂度：O(2^n * n^2)，共 2^n * n 个状态、每状态枚举邻边；空间复杂度：O(2^n * n)，vis 数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestPathLength(vector<vector<int>>& graph) {  // graph 是邻接表；返回访问所有节点所需的最短步数
        int n = graph.size();  // 节点个数，也决定状态掩码的位数
        queue<pair<int, int>> q;  // BFS 队列，元素是（当前节点, 已访问节点掩码）
        bool vis[n][1 << n];  // vis[i][mask] 记录状态是否入队，避免重复扩展
        memset(vis, false, sizeof(vis));  // 所有状态初始都未访问
        for (int i = 0; i < n; ++i) {  // 每个节点都可以作为起点，因此把 n 个初始状态一起入队
            q.emplace(i, 1 << i);  // 起点 i 的掩码只有第 i 位为 1
            vis[i][1 << i] = true;  // 标记该初始状态已访问
        }  // 初始化结束
        for (int ans = 0;; ++ans) {  // BFS 按层推进，ans 就是当前步数；队列非空时一定能在某层返回
            for (int k = q.size(); k; --k) {  // 当前层有 k 个状态，一次只扩展这一层
                auto [i, st] = q.front();  // 取出队首状态：当前在节点 i，已访问集合为 st
                q.pop();  // 弹出队首
                if (st == (1 << n) - 1) {  // 掩码覆盖了全部 n 位，说明所有节点都访问过
                    return ans;  // 返回当前步数，BFS 保证这是最短的
                }  // 到达终点判断结束
                for (int j : graph[i]) {  // 枚举节点 i 的所有邻居
                    int nst = st | 1 << j;  // 走一步到 j，掩码加上第 j 位
                    if (!vis[j][nst]) {  // 该状态没访问过才入队，防止重复搜索
                        vis[j][nst] = true;  // 标记状态已访问
                        q.emplace(j, nst);  // 把新状态加入队尾，等待下一层扩展
                    }  // 邻居枚举结束
                }  // 本层状态扩展结束
            }  // 层数加一，进入下一步
        }  // 外层循环结束
    }  // 方法结束
};  // 类定义结束