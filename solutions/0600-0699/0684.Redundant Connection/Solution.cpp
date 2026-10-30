// 题目：684. 冗余连接（Redundant Connection）
// 思路：并查集按顺序加入每条边，若某条边的两个端点已经在同一集合中，这条边就会成环，它就是答案。
// 时间复杂度：O(n α(n))，并查集单次操作近似常数；空间复杂度：O(n)，父数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {  // edges：按顺序给出的边
        int n = edges.size();  // 节点数：n 个点、n 条边
        vector<int> p(n);  // 并查集父数组，下标 0..n-1 对应节点 1..n
        iota(p.begin(), p.end(), 0);  // 初始时每个节点各自构成一个集合
        function<int(int)> find = [&](int x) {  // 递归找根，同时做路径压缩
            return x == p[x] ? x : p[x] = find(p[x]);  // 自己是根就返回，否则把父指针直接指向根
        };
        for (int i = 0;; ++i) {  // 逐条加边；题目保证一定有解，所以省略循环上界
            int pa = find(edges[i][0] - 1);  // 起点所在集合的根（输入是 1-based，减 1 转成下标）
            int pb = find(edges[i][1] - 1);  // 终点所在集合的根
            if (pa == pb) {  // 两个端点原本已连通，再加这条边就会成环
                return edges[i];  // 这条边就是多余的边
            }
            p[pa] = pb;  // 合并两个集合：把一棵树的根挂到另一棵上
        }
    }
};
