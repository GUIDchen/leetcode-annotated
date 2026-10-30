// 题目：3108. 带权图里旅途的最小代价（Minimum Cost Walk in Weighted Graph）
// 思路：并查集求出连通分量，把同一分量内所有边权按位与起来（同一个分量内可以反复绕行，路径代价就是这些边的与）；查询时同点返回 0、同分量返回与值、否则 -1。
// 时间复杂度：O((V + E + Q) α(V))，并查集近似常数；空间复杂度：O(V)，存父数组、大小数组与分量代价。
class UnionFind {  // 并查集：维护连通分量，支持按大小合并与路径压缩
public:  // 对外提供构造、合并、查找、查大小
    UnionFind(int n) {  // 构造：n 个结点，初始各自成一个集合
        p = vector<int>(n);  // p[i] 表示 i 的父结点
        size = vector<int>(n, 1);  // size[i] 只在 i 是根时有效，表示集合大小
        iota(p.begin(), p.end(), 0);  // 初始时每个结点的父结点就是它自己
    }

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回是否真的发生了合并
        int pa = find(a), pb = find(b);  // 分别找到两个根
        if (pa == pb) {  // 本来就在同一集合
            return false;  // 不需要合并
        }
        if (size[pa] > size[pb]) {  // 让小树挂到大树上，控制树高
            p[pb] = pa;  // b 的根改为指向 a 的根
            size[pa] += size[pb];  // 新根的大小要加上被并入的集合
        } else {  // 否则让 pa 挂到 pb 上
            p[pa] = pb;  // a 的根改为指向 b 的根
            size[pb] += size[pa];  // 更新新根的大小
        }
        return true;  // 合并成功
    }

    int find(int x) {  // 查找 x 所在集合的根，同时做路径压缩
        if (p[x] != x) {  // x 还不是根
            p[x] = find(p[x]);  // 递归找到根，并把 x 直接挂到根上
        }
        return p[x];  // 返回根结点
    }

    int getSize(int x) {  // 查询 x 所在集合的大小
        return size[find(x)];  // 先找到根，再取该根上记录的大小
    }

private:  // 内部数据
    vector<int> p, size;  // 父结点数组与集合大小数组
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {  // n：点数；edges：带权边；query：查询对
        g = vector<int>(n, -1);  // g[root] 存该分量内所有边权的按位与，-1 是全 1 掩码，便于与运算起步
        uf = new UnionFind(n);  // 建立并查集
        for (auto& e : edges) {  // 第一遍：把每条边的两个端点合并，得到连通分量
            uf->unite(e[0], e[1]);  // 合并这条边的两个端点
        }
        for (auto& e : edges) {  // 第二遍：把每条边的权值按位与到所属分量上
            int root = uf->find(e[0]);  // 该边所属连通分量的根
            g[root] &= e[2];  // 反复与运算，最终得到该分量的最小可走代价
        }
        vector<int> ans;  // 存放每个查询的答案
        for (auto& q : query) {  // 逐个回答查询
            ans.push_back(f(q[0], q[1]));  // 用辅助函数 f 算出这一对点的最小代价
        }
        return ans;  // 返回所有查询的答案
    }

private:  // 内部数据与辅助方法
    UnionFind* uf;  // 并查集指针
    vector<int> g;  // 按根记录每个分量的边权与值

    int f(int u, int v) {  // 返回从 u 走到 v 的最小代价
        if (u == v) {  // 起点就是终点
            return 0;  // 不用走任何边，代价为 0
        }
        int a = uf->find(u), b = uf->find(v);  // 分别求两个端点的根
        return a == b ? g[a] : -1;  // 同一分量返回该分量的与值，否则不连通返回 -1
    }
};