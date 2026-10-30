class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {  // nodes：节点总数；parent：每个节点的父节点；value：每个节点的值
        vector<vector<int>> g(nodes);  // 邻接表表示这棵树：g[u] 存 u 的所有孩子
        for (int i = 1; i < nodes; ++i) {  // 0 号节点是根，从 1 号开始把节点挂到父节点下
            g[parent[i]].emplace_back(i);  // 把节点 i 接到它的父节点 parent[i] 后面
        }  // 结束建图循环
        function<pair<int, int>(int)> dfs = [&](int i) -> pair<int, int> {  // dfs(i)：返回以 i 为根的 (子树值之和, 保留下来的节点个数)
            int s = value[i], m = 1;  // s 累加子树值（初值为当前节点值），m 是节点个数（初值为 1）
            for (int j : g[i]) {  // 遍历当前节点的所有孩子
                auto [t, n] = dfs(j);  // 递归求出孩子子树的「值之和」t 与「节点个数」n
                s += t;  // 累加孩子的值之和
                m += n;  // 累加孩子的节点个数
            }  // 结束孩子遍历
            if (s == 0) {  // 子树值之和为 0，说明这棵子树要被整体删除
                m = 0;  // 节点数记 0，表示这一整棵子树不再保留
            }  // 结束 if 判断
            return pair<int, int>{s, m};  // 返回本子树的 (值之和, 节点个数)
        };  // lambda 定义结束
        return dfs(0).second;  // 答案就是根子树保留下来的节点个数
    }  // deleteTreeNodes 方法结束
};  // Solution 类定义结束
