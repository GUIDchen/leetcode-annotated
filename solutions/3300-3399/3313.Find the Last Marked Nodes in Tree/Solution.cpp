// 题目：3313. 查找树中最后标记的节点（Find the Last Marked Nodes in Tree）🔒
// 核心思路：先从节点 0 出发 DFS 求最远点 a，再从 a 求最远点 b，a、b 就是树直径的两端；每个节点比较到 a、b 的距离，取更远的那端作为最后标记它的节点。
// 时间复杂度：三次 DFS 合计 O(n)；空间复杂度：O(n)，用于邻接表与三个距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> lastMarkedNodes(vector<vector<int>>& edges) {  // edges：树的 n-1 条无向边；返回每个节点最后被标记的邻居编号
        int n = edges.size() + 1;  // 边数 +1 就是节点个数（树的性质）
        g.resize(n);  // 邻接表按节点数开好容量（g 是成员变量，可被多次调用复用）
        for (const auto& e : edges) {  // 逐条边建无向图
            int u = e[0], v = e[1];  // 取出这条边的两个端点
            g[u].push_back(v);  // u 的邻居中加入 v
            g[v].push_back(u);  // v 的邻居中加入 u（无向边要双向记录）
        }  // 建图结束
        vector<int> dist1(n);  // dist1[i]：节点 i 到起点 0 的树上距离
        dfs(0, -1, dist1);  // 从节点 0 出发 DFS 填距离，-1 表示它没有父节点
        int a = max_element(dist1.begin(), dist1.end()) - dist1.begin();  // 离 0 最远的点一定可以取作直径的一个端点 a

        vector<int> dist2(n);  // dist2[i]：节点 i 到端点 a 的距离
        dfs(a, -1, dist2);  // 以 a 为根再跑一次 DFS
        int b = max_element(dist2.begin(), dist2.end()) - dist2.begin();  // 离 a 最远的点就是直径的另一个端点 b

        vector<int> dist3(n);  // dist3[i]：节点 i 到端点 b 的距离
        dfs(b, -1, dist3);  // 以 b 为根再跑一次 DFS

        vector<int> ans;  // ans[i]：从节点 i 出发时最后被标记的节点
        for (int i = 0; i < n; ++i) {  // 对每个节点单独比较它到两个直径端点的距离
            ans.push_back(dist2[i] > dist3[i] ? a : b);  // 距离更远的那端会最后标记到它（相等时取 b，题目允许任选）
        }  // 遍历结束
        return ans;  // 返回每个节点最后被标记的邻居编号
    }  // lastMarkedNodes 方法结束

private:  // 以下是内部辅助成员
    vector<vector<int>> g;  // 邻接表：g[u] 保存与 u 相邻的所有节点

    void dfs(int i, int fa, vector<int>& dist) {  // i：当前节点；fa：父节点（防止走回头路）；dist：距离数组（按引用回填）
        for (int j : g[i]) {  // 枚举当前节点的所有邻居
            if (j != fa) {  // 跳过父节点，这样在树上就不会绕回已访问的点
                dist[j] = dist[i] + 1;  // 子节点距离 = 当前节点距离 + 1
                dfs(j, i, dist);  // 递归处理子节点，当前节点成为它的父节点
            }  // if 结束
        }  // for 结束
    }  // dfs 结束
};  // 类定义结束（LeetCode 只要求实现这个类）
