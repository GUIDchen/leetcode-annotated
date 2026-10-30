// 题目：1489. 找到最小生成树里的关键边和伪关键边（Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree）
// 核心思路：先排序求基准 MST 权值 v；对每条边「禁用后重跑 Kruskal」判断关键边，「强制选中后重跑」判断伪关键边。
// 时间复杂度：O(E log E + E^2 α(n))，只需排序一次，之后对每条边各跑一遍并查集；空间复杂度：O(n + E)。
class UnionFind {  // 并查集：维护连通分量，供 Kruskal 使用
public:  // 成员对外可见（题解里直接读 p 与 n）
    vector<int> p;  // p[x]：x 的父节点，根节点满足 p[x] == x
    int n;  // 当前连通分量个数，用于判断图是否连通

    UnionFind(int _n)  // 构造：初始化 n 个独立节点
        : n(_n)  // 分量数初始等于节点数
        , p(_n) {  // 父数组大小为 _n
        iota(p.begin(), p.end(), 0);  // 填 0,1,2,...，让每个节点自成一个分量
    }  // 构造函数结束

    bool unite(int a, int b) {  // 合并 a、b 所在分量，成功说明这条边被选入 MST
        if (find(a) == find(b)) return false;  // 已连通则合并无效（成环），返回 false
        p[find(a)] = find(b);  // 把 a 的根挂到 b 的根下
        --n;  // 分量数减一
        return true;  // 返回合并成功
    }  // unite 方法结束

    int find(int x) {  // 查根，带路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // 递归把沿途节点直接挂到根上
        return p[x];  // 返回根节点
    }  // find 方法结束
};  // UnionFind 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {  // n：节点数；edges：{u, v, w} 边列表；返回 [关键边下标, 伪关键边下标]
        for (int i = 0; i < edges.size(); ++i) edges[i].push_back(i);  // 给每条边追加原始下标，排序后仍能认出它
        sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return a[2] < b[2]; });  // 按边权升序排列，这是 Kruskal 的前提
        int v = 0;  // 记录最小生成树的权值和
        UnionFind uf(n);  // 求一次基准 MST 用的并查集
        for (auto& e : edges) {  // 标准 Kruskal 求基准权值和 v
            int f = e[0], t = e[1], w = e[2];  // 拆出起点、终点、边权
            if (uf.unite(f, t)) v += w;  // 能合并说明该边连接两个不同分量，选入 MST 并累加权值
        }  // 基准 Kruskal 循环结束
        vector<vector<int>> ans(2);  // ans[0] 存关键边，ans[1] 存伪关键边
        for (auto& e : edges) {  // 逐条边判断它在 MST 中的角色
            int f = e[0], t = e[1], w = e[2], i = e[3];  // 拆出端点、权值与原始编号
            UnionFind ufa(n);  // 场景一：禁用这条边后重建 MST
            int k = 0;  // 禁用该边后得到的 MST 权值和
            for (auto& ne : edges) {  // 跳过该边跑 Kruskal
                int x = ne[0], y = ne[1], z = ne[2], j = ne[3];  // 另一条边的端点、权值与编号
                if (j != i && ufa.unite(x, y)) k += z;  // 边不同且能合并，才选入并累加权值
            }  // 内层 Kruskal 循环结束
            if (ufa.n > 1 || (ufa.n == 1 && k > v)) {  // 图不连通或权值变大，说明该边不可替代，是关键边
                ans[0].push_back(i);  // 记入关键边集合
                continue;  // 关键边不再参与伪关键边判定
            }  // if 分支结束

            UnionFind ufb(n);  // 场景二：强制把这条边先加入 MST
            ufb.unite(f, t);  // 先合并该边两端点
            k = w;  // 权值和先计入这条边
            for (auto& ne : edges) {  // 在强制选它的前提下继续 Kruskal
                int x = ne[0], y = ne[1], z = ne[2], j = ne[3];  // 另一条边的端点、权值与编号
                if (j != i && ufb.unite(x, y)) k += z;  // 边不同且能合并，才选入并累加权值
            }  // 内层 Kruskal 循环结束
            if (k == v) ans[1].push_back(i);  // 仍能得到最小权值和，说明它是伪关键边
        }  // 外层循环结束
        return ans;  // 返回 [关键边, 伪关键边] 两个列表
    }  // 方法结束
};  // Solution 类定义结束