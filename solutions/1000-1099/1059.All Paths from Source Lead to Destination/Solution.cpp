// 题目：1059. 从起点到终点的所有路径（All Paths from Source Lead to Destination）
// 思路：建邻接表后从 source 做 DFS，用三色标记（0 未访问、1 访问中、2 已验证）检测环，并要求所有出度为 0 的节点都必须是 destination。
// 时间复杂度：O(n + E)，每个点与每条边只处理一次；空间复杂度：O(n + E)，邻接表与状态数组。
class Solution {  // LeetCode 约定的题解类
public:  // 以下成员对外可见
    vector<vector<int>> g;  // 邻接表：g[u] 是节点 u 的所有后继
    vector<int> st;  // 节点状态：0 未访问，1 正在访问，2 已验证全部路径合法
    int destination;  // 终点编号，用成员变量保存，省去递归传参

    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {  // 判断从 source 出发的所有路径是否都终止于 destination
        this->destination = destination;  // 保存终点（形参同名，必须用 this-> 区分）
        g.assign(n, {});  // 邻接表初始化为 n 个空列表
        for (auto& e : edges) {  // 遍历每条有向边
            g[e[0]].push_back(e[1]);  // 建立 e[0] -> e[1] 的边
        }  // 建图结束
        if (!g[destination].empty()) {  // 终点还有出边，说明存在路径没有在终点结束
            return false;  // 直接返回假
        }  // 检查结束
        st.assign(n, 0);  // 所有节点初始化为未访问
        return dfs(source);  // 从起点开始深度优先搜索
    }  // 方法结束

    bool dfs(int i) {  // 返回以 i 为起点的所有路径是否都终止于终点
        if (st[i] != 0) {  // 该节点已经访问过
            return st[i] == 2;  // 状态 2 表示已验证通过；状态 1 表示发现环，返回假
        }  // 记忆化判断结束
        if (g[i].empty()) {  // 出度为 0 的死胡同节点
            return i == destination;  // 只有恰好是终点才合法
        }  // 死胡同判断结束
        st[i] = 1;  // 标记为「正在访问」，供环检测使用
        for (int j : g[i]) {  // 遍历所有后继节点
            if (!dfs(j)) {  // 某条后继路径不合法
                return false;  // 整体不合法，返回假
            }  // 后继判断结束
        }  // 所有后继处理完毕
        st[i] = 2;  // 标记为已验证，后续再访问可直接复用结论
        return true;  // 以 i 为起点的所有路径都合法
    }  // dfs 结束
};  // 类定义结束
