// 题目：1724. 检查边长度限制的路径是否存在 II（Checking Existence of Edge Length Limited Paths II）难度：困难
// 思路：把所有边按权值升序依次加入“持久化并查集”，每次合并时记下合并发生的时刻（边权）version，只按秩合并且不路径压缩，
// 于是历史版本不会被破坏；查询时 find(x, limit) 只沿“合并时刻 < limit”的父边向上走，两边落在同一根即说明存在只含小于 limit 的路径。
// 时间复杂度：构造 O(m log m + m log n)，单次查询 O(log n)；空间复杂度：O(n + m)，并查集数组。
class PersistentUnionFind {  // 持久化并查集：可按“时刻 t”回溯到历史状态
private:  // 内部数据结构不对外暴露
    vector<int> rank;  // 每个集合的秩（树的近似高度），用于按秩合并
    vector<int> parent;  // 父节点数组，根节点的父节点是它自己
    vector<int> version;  // version[x]：x 被挂到新父节点上的时刻（边权）

public:  // 对外提供构造、查找与合并
    PersistentUnionFind(int n)  // n：节点个数
        : rank(n, 0)  // 秩初始化为 0
        , parent(n)  // 父数组先占位
        , version(n, INT_MAX) {  // 版本号初始为无穷大：表示“在任何时刻都已存在”的根边
        for (int i = 0; i < n; i++) {  // 逐个节点初始化
            parent[i] = i;  // 初始时每个节点自成一个集合
        }
    }  // 构造函数结束

    int find(int x, int t) {  // 在“时刻 t”的版本下查找 x 的根
        if (parent[x] == x || version[x] >= t) {  // 已是根，或挂父节点的时刻晚于 t（此时该边还没加入）
            return x;  // 那么 x 自己就是当前版本下的根
        }
        return find(parent[x], t);  // 否则继续沿父指针向上查找（不压缩路径，保留历史）
    }  // find 方法结束

    bool unionSet(int a, int b, int t) {  // 在时刻 t 合并 a、b 所在集合
        int pa = find(a, INT_MAX);  // 取 a 在最新版本下的根
        int pb = find(b, INT_MAX);  // 取 b 在最新版本下的根
        if (pa == pb) {  // 已经在同一个集合里
            return false;  // 无需合并，返回 false 表示这条边被忽略
        }
        if (rank[pa] > rank[pb]) {  // 按秩合并：把矮树挂到高树下
            version[pb] = t;  // 记录 b 的根挂到 a 的根上的时刻
            parent[pb] = pa;  // 修改父指针完成合并
        } else {  // 反之把 a 的根挂到 b 的根下
            version[pa] = t;  // 记录 a 的根挂到 b 的根上的时刻
            parent[pa] = pb;  // 修改父指针完成合并
            if (rank[pa] == rank[pb]) {  // 两棵树等高
                rank[pb]++;  // 合并后高度加一，维持按秩合并的正确性
            }
        }
        return true;  // 合并成功
    }  // unionSet 方法结束
};  // PersistentUnionFind 类结束

class DistanceLimitedPathsExist {  // 题面要求实现的类
private:  // 内部只保存一个持久化并查集
    PersistentUnionFind puf;  // puf：按边权升序逐步合并得到的持久化并查集

public:  // 对外提供构造与查询
    DistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList)  // n：节点数；edgeList：边的三元组 (u, v, dis)
        : puf(n) {  // 用节点数初始化并查集
        sort(edgeList.begin(), edgeList.end(),  // 把边按权值升序排序
            [](const vector<int>& a, const vector<int>& b) {  // 比较器：只看第三个数（边权）
                return a[2] < b[2];  // 权值小的边排在前面
            });

        for (const auto& edge : edgeList) {  // 按权值从小到大依次加边
            puf.unionSet(edge[0], edge[1], edge[2]);  // 用边权作为合并时刻，合并这条边的两个端点
        }
    }  // 构造函数结束

    bool query(int p, int q, int limit) {  // p、q：查询的起终点；limit：路径上每条边都必须严格小于它
        return puf.find(p, limit) == puf.find(q, limit);  // 只看 limit 之前合并的边，同根即说明存在合法路径
    }  // query 方法结束
};  // DistanceLimitedPathsExist 类结束

/**
 * Your DistanceLimitedPathsExist object will be instantiated and called as such:
 * DistanceLimitedPathsExist* obj = new DistanceLimitedPathsExist(n, edgeList);
 * bool param_1 = obj->query(p,q,limit);
 */