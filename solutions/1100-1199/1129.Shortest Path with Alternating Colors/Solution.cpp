// 题目：1129. 颜色交替的最短路径（Shortest Path with Alternating Colors）
// 思路：以 (节点, 到达该节点所用边的颜色) 为状态做 BFS：队列初始放入 (0, 红) 与 (0, 蓝) 两个虚拟起点，扩展时把颜色取反再沿该颜色的出边走，状态第一次被访问时的层数就是最短交替路径长度。
// 时间复杂度：O(n + e)，每个 (节点, 颜色) 状态最多入队一次；空间复杂度 O(n + e)，需要存图与访问标记。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {  // n：节点数；redEdges/blueEdges：红蓝边；返回到各节点的最短交替路径长度
        vector<vector<vector<int>>> g(2, vector<vector<int>>(n));  // g[颜色][起点] 存该颜色出边的终点，颜色 0 红、1 蓝
        for (auto& e : redEdges) {  // 建立红色有向边
            g[0][e[0]].push_back(e[1]);  // 红边 e[0] → e[1]
        }  // 红边建图结束
        for (auto& e : blueEdges) {  // 建立蓝色有向边
            g[1][e[0]].push_back(e[1]);  // 蓝边 e[0] → e[1]
        }  // 蓝边建图结束
        queue<pair<int, int>> q;  // BFS 队列，元素为 (节点, 到达该节点所用边的颜色)
        q.emplace(0, 0);  // 节点 0 以「虚拟红边到达」入队，便于第一步走蓝边
        q.emplace(0, 1);  // 节点 0 以「虚拟蓝边到达」入队，便于第一步走红边
        bool vis[n][2];  // vis[i][c]：是否已用颜色 c 的边到达过节点 i
        memset(vis, false, sizeof vis);  // 访问标记清零
        vector<int> ans(n, -1);  // 答案初始化为 -1，表示不可达
        int d = 0;  // d：当前 BFS 层数，即已走过的边数
        while (!q.empty()) {  // 队列非空就继续扩展
            for (int k = q.size(); k; --k) {  // 按层处理，保证同层节点距离都等于 d
                auto [i, c] = q.front();  // 取出队首节点 i 与到达它所用的颜色 c
                q.pop();  // 弹出队首
                if (ans[i] == -1) {  // 第一次到达该节点即为最短距离
                    ans[i] = d;  // 记录最短交替路径长度
                }  // if 分支结束
                vis[i][c] = true;  // 标记该状态已访问，避免同类状态重复入队
                c ^= 1;  // 下一条边必须换成相反颜色
                for (int& j : g[c][i]) {  // 遍历新颜色下的所有出边
                    if (!vis[j][c]) {  // 目标状态未访问过才入队
                        q.emplace(j, c);  // 把 (终点, 新颜色) 入队
                    }  // if 分支结束
                }  // 出边循环结束
            }  // 本层循环结束
            ++d;  // 本层处理完，距离加一
        }  // while 循环结束
        return ans;  // 返回到各节点的最短交替路径长度
    }  // 方法结束
};  // 类定义结束