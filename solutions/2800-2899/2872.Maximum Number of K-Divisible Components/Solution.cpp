// 题目：2872. 可以被 K 整除连通块的最大数目（Maximum Number of K-Divisible Components）
// 思路：以 0 为根做后序 DFS，某棵子树的和能被 k 整除就把它切下来成为一块，只把余数部分向上合并。
// 时间复杂度：O(n)，每个节点与每条边只访问一次；空间复杂度：O(n)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {  // n 是节点数，edges 是无向边，values 是各节点权值，k 是整除因子
        int ans = 0;  // 可切出的连通块计数
        vector<int> g[n];  // 邻接表：g[u] 保存所有与 u 相邻的节点（变长数组，长度由参数 n 决定）
        for (auto& e : edges) {  // 逐条边建图
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻居里加入 b
            g[b].push_back(a);  // b 的邻居里加入 a（无向图要双向添加）
        }  // 建图结束
        auto dfs = [&](this auto&& dfs, int i, int fa) -> long long {  // C++23 显式对象参数的递归 lambda：i 为当前节点，fa 为父节点，返回子树和
            long long s = values[i];  // 以 i 为根的子树和，先算上自己的权值
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 跳过父节点，避免走回头路
                    s += dfs(j, i);  // 把子树的贡献累加进来
                }  // 子节点处理结束
            }  // 邻居遍历结束
            ans += s % k == 0;  // 子树和能被 k 整除，说明可以在这里切出一块，布尔值直接累加
            return s;  // 把当前子树和返回给父节点
        };  // lambda 定义结束
        dfs(0, -1);  // 从 0 号节点开始 DFS，根的父节点记为 -1
        return ans;  // 返回最多能切出的连通块数目
    }  // 方法结束
};  // 类定义结束
