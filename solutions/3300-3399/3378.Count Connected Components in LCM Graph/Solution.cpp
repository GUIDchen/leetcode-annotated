// 题目：3378. 统计最小公倍数图中的连通块数目（Count Connected Components in LCM Graph）
// 思路：两点连边等价于存在 g ≤ threshold 同时整除两者。用并查集把每个 num 与它不超过 threshold 的所有倍数合并，最后统计不同代表（> threshold 的数自成一块）的个数。
// 时间复杂度：O((n + threshold) · log threshold · α)；空间复杂度：O(threshold)。
typedef struct DSU {  // 并查集：维护「最小公倍数 ≤ threshold」的连通关系
    unordered_map<int, int> par, rank;  // par：父节点映射；rank：按秩合并的秩（与 std::rank 无关，是成员名）
    DSU(int n) {  // 构造函数：n 通常传入 threshold，为 0..n-1 建集合
        for (int i = 0; i < n; ++i) {  // 逐点为每个元素建立独立集合
            par[i] = i;  // 初始时每个点的父节点都是自己
            rank[i] = 0;  // 初始秩为 0
        }  // 初始化循环结束
    }  // 构造函数结束

    void makeSet(int v) {  // 单独建一个集合（本解法未调用，保留并查集模板接口）
        par[v] = v;  // 父节点指向自己
        rank[v] = 1;  // 秩置为 1
    }  // makeSet 方法结束

    int find(int x) {  // 查根，并做路径压缩
        if (par[x] == x) {  // 自己就是根节点
            return x;  // 直接返回
        }  // 递归边界结束
        return par[x] = find(par[x]);  // 递归找到根后把 x 的父节点直接改成根，压缩路径
    }  // find 方法结束

    void unionSet(int u, int v) {  // 合并 u、v 所在的两个集合
        u = find(u);  // 先找到 u 的根
        v = find(v);  // 再找到 v 的根
        if (u != v) {  // 根不同才需要真正合并
            if (rank[u] < rank[v]) swap(u, v);  // 保证 u 是秩较大的根，减少树高
            par[v] = u;  // 把秩小的树挂到秩大的树下
            if (rank[u] == rank[v]) rank[u]++;  // 两树秩相同时，合并后秩加一
        }  // 合并分支结束
    }  // unionSet 方法结束
} DSU;  // 结构体定义结束，并用 typedef 起别名 DSU

class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int countComponents(vector<int>& nums, int threshold) {  // nums：图中的数字；threshold：允许的最小公倍数上界
        DSU dsu(threshold);  // 用 0..threshold-1 建并查集（threshold 本身会在合并时按需插入）
        for (auto& num : nums) {  // 枚举每个给定数字
            for (int j = num; j <= threshold; j += num) {  // 枚举 num 的所有倍数 j（含 num 自己，且不超过 threshold）
                dsu.unionSet(num, j);  // lcm(num, j) = j ≤ threshold，所以 num 与 j 必须属于同一连通块
            }  // 倍数枚举结束
        }  // 数字枚举结束
        unordered_set<int> par;  // 用集合统计每个连通块的代表，自动去重
        for (auto& num : nums) {  // 再遍历一次所有数字
            if (num > threshold) {  // 大于 threshold 的数不可能与任何数构成合法 lcm
                par.insert(num);  // 因此它自成一个连通块，直接把自己作为代表
            } else {  // 否则它已经被合并进某个集合
                par.insert(dsu.find(num));  // 取它所在集合的根作为代表
            }  // 分支结束
        }  // 统计循环结束
        return par.size();  // 不同代表的个数就是连通块数目
    }  // countComponents 方法结束
};  // Solution 类定义结束
