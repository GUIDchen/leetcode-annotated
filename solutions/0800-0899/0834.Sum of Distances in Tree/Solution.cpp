// 题目：834. 树中距离之和（Sum of Distances in Tree）
// 思路：两遍 DFS。第一遍以 0 为根求出每个结点的子树大小与根的距离和 ans[0]；第二遍用换根公式 ans[j] = ans[i] + n - 2·size[j] 自上而下推出全部答案。
// 时间复杂度：O(n)，每个结点被两遍 DFS 各访问一次；空间复杂度：O(n)，邻接表加 ans、size 两个数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {  // n 为结点个数，edges 是 n-1 条无向边，共同构成一棵树
        vector<vector<int>> g(n);  // 邻接表：g[i] 存放结点 i 的所有邻居
        for (auto& e : edges) {  // 逐条边建图
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a 的邻居中加入 b
            g[b].push_back(a);  // b 的邻居中加入 a（无向边双向添加）
        }  // 建图结束
        vector<int> ans(n);  // ans[i] 表示结点 i 到其余所有结点的距离之和
        vector<int> size(n);  // size[i] 表示以 i 为根的子树的结点个数

        function<void(int, int, int)> dfs1 = [&](int i, int fa, int d) {  // 第一遍后序 DFS：i 当前结点，fa 父结点，d 是 i 到根 0 的距离
            ans[0] += d;  // 把结点 i 到根的距离累加，最终得到根结点的距离和 ans[0]
            size[i] = 1;  // 子树大小先计入结点自己
            for (int& j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 跳过父结点，避免沿来路边回走
                    dfs1(j, i, d + 1);  // 先递归求出子结点 j 的子树，深度加一
                    size[i] += size[j];  // 后序累加：子树 j 的大小加到 i 上
                }  // if 结束
            }  // 内层 for 结束
        };  // lambda 定义结束

        function<void(int, int, int)> dfs2 = [&](int i, int fa, int t) {  // 第二遍先序 DFS：i 当前结点，fa 父结点，t 是结点 i 的距离和
            ans[i] = t;  // 直接记录当前结点的答案
            for (int& j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 只沿子树方向递归，跳过父结点
                    dfs2(j, i, t - size[j] + n - size[j]);  // 换根公式：子树内 size[j] 个点距离减 1，其余 n-size[j] 个点距离加 1
                }  // if 结束
            }  // for 结束
        };  // lambda 定义结束

        dfs1(0, -1, 0);  // 以 0 为根做第一次 DFS，得到 ans[0] 与全部子树大小
        dfs2(0, -1, ans[0]);  // 以 ans[0] 为起点做第二次 DFS，逐层换根求出所有结点答案
        return ans;  // 返回答案数组
    }  // 方法结束
};
