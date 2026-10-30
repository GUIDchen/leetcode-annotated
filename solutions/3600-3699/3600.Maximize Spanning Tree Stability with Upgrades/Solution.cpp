// 3600. 升级后最大生成树稳定性（Maximize Spanning Tree Stability with Upgrades）
// 核心思路：先判必选边是否成环以及原图是否连通，再对答案二分；判定用并查集优先并入原稳定性已达标（s >= lim）的边，再用至多 k 条升级可达标的边收尾，看能否连通。
// 复杂度：时间 O(m log C · α(n))，空间 O(n + m)，其中 C 为稳定性上界、α 为并查集反阿克曼函数。
class UnionFind {  // 并查集：维护连通分量与分量大小
public:  // 对外接口
    vector<int> p, size;  // 父指针数组与每个集合的大小
    int cnt;  // 当前连通分量个数

    UnionFind(int n) {  // 构造 n 个单点集合
        p.resize(n);  // 父数组扩容
        size.assign(n, 1);  // 每个集合初始大小为 1
        cnt = n;  // 初始有 n 个连通分量
        for (int i = 0; i < n; i++) p[i] = i;  // 每个节点自成一派
    }  // 构造函数结束

    int find(int x) {  // 查根，带路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // 不是根就把父指针直接挂到根上
        return p[x];  // 返回根节点
    }  // find 结束

    bool unite(int a, int b) {  // 合并两个集合，成功合并返回 true
        int pa = find(a), pb = find(b);  // 分别求出两个端点所在集合的根
        if (pa == pb) return false;  // 已经在同一集合，无需合并
        if (size[pa] > size[pb]) {  // 按大小合并：把小集合挂到大集合上
            p[pb] = pa;  // pb 挂到 pa
            size[pa] += size[pb];  // 更新 pa 集合的大小
        } else {  // 否则反向挂
            p[pa] = pb;  // pa 挂到 pb
            size[pb] += size[pa];  // 更新 pb 集合的大小
        }  // if 结束
        cnt--;  // 合并成功后连通分量数减一
        return true;  // 合并成功
    }  // unite 结束
};  // UnionFind 定义结束

class Solution {  // 主解类
public:  // 对外接口
    int n, k;  // 点数与可用升级次数
    vector<vector<int>> edges;  // 边表，每条边为 (u, v, 稳定性 s, 是否必选 must)

    bool check(int lim) {  // 判定能否让生成树中每条边的稳定性都 >= lim
        UnionFind uf(n);  // 新建并查集

        for (auto& e : edges) {  // 第一轮：先并入不需要升级就已达标的边
            int u = e[0], v = e[1], s = e[2];  // 取出端点与稳定性
            if (s >= lim) {  // 原稳定性已达标
                uf.unite(u, v);  // 直接并入生成树
            }  // if 结束
        }  // 循环结束

        int rem = k;  // 剩余可用的升级次数
        for (auto& e : edges) {  // 第二轮：用升级一次即可达标的边继续连通
            int u = e[0], v = e[1], s = e[2];  // 取出端点与稳定性
            if (s * 2 >= lim && rem > 0) {  // 升级后达标且还有升级次数
                if (uf.unite(u, v)) {  // 这条边确实能合并两个不同的连通分量
                    rem--;  // 消耗一次升级次数
                }  // if 结束
            }  // if 结束
        }  // 循环结束

        return uf.cnt == 1;  // 只剩一个连通分量说明所有点都能连通
    }  // check 结束

    int maxStability(int n, vector<vector<int>>& edges, int k) {  // 入口：二分求最大可行的稳定性下界
        this->n = n;  // 保存点数供 check 使用
        this->edges = edges;  // 保存边表供 check 使用
        this->k = k;  // 保存升级次数供 check 使用

        UnionFind uf(n);  // 单独一个并查集用于必选边的合法性检查
        int mn = 1e6;  // 答案的上界：必选边稳定性的最小值

        for (auto& e : edges) {  // 先处理必选边
            int u = e[0], v = e[1], s = e[2], must = e[3];  // 取出两个端点、稳定性与必选标记
            if (must) {  // m 为真说明是必选边
                mn = min(mn, s);  // 答案不会超过必选边中的最小稳定性
                if (!uf.unite(u, v)) {  // 必选边导致成环
                    return -1;  // 无法构成合法生成树
                }  // if 结束
            }  // if 结束
        }  // 循环结束

        for (auto& e : edges) {  // 再用全部边检查整张图的连通性
            uf.unite(e[0], e[1]);  // 合并该边的两个端点
        }  // 循环结束

        if (uf.cnt > 1) {  // 原图本身就不连通
            return -1;  // 不存在生成树，返回 -1
        }  // if 结束

        int l = 1, r = mn;  // 二分区间：答案在 [1, mn] 内
        while (l < r) {  // 找最大的可行值
            int mid = (l + r + 1) >> 1;  // 上取整的中点，避免死循环
            if (check(mid)) {  // mid 可行
                l = mid;  // 尝试更大的下界
            } else {  // mid 不可行
                r = mid - 1;  // 缩小上界
            }  // if 结束
        }  // while 结束

        return l;  // l 即最大可行的稳定性
    }  // maxStability 结束
};  // 类定义结束
