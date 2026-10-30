// 3873. 添加一个点后可激活的最大点数（Maximum Points Activated with One Addition）
// 核心思路：把点 (x, y) 看成边 x -- (y + 大偏移) 做并查集合并，连通分量即一条线上互相可达的点集；若加一个点，可以把两个分量连起来，答案是最大分量 + 次大分量 + 1。
// 复杂度：时间复杂度 O(n·α(n))，空间复杂度 O(n)。
class UnionFind {  // 并查集类
public:  // 公有成员
    unordered_map<long long, long long> p;  // 父指针表（懒初始化）
    unordered_map<long long, int> sz;  // 每个集合的大小

    long long find(long long x) {  // 查找 x 所在集合的根
        if (!p.count(x)) {  // x 第一次出现
            p[x] = x;  // 自己是自己的父节点
            sz[x] = 1;  // 集合大小初始为 1
        }  // 初始化结束
        if (p[x] != x) {  // x 不是根节点
            p[x] = find(p[x]);  // 路径压缩，把根直接挂成父节点
        }  // 压缩判断结束
        return p[x];  // 返回根节点
    }  // find 结束

    bool unite(long long a, long long b) {  // 合并 a、b 两个集合
        long long pa = find(a), pb = find(b);  // 分别求出两个集合的根
        if (pa == pb) return false;  // 已经同属一个集合，无需合并

        if (sz[pa] > sz[pb]) {  // 按大小合并：pa 更大
            p[pb] = pa;  // 小集合挂到大集合上
            sz[pa] += sz[pb];  // 更新大集合大小
        } else {  // pb 不小于 pa
            p[pa] = pb;  // 把 pa 挂到 pb 上
            sz[pb] += sz[pa];  // 更新 pb 的大小
        }  // 合并方向判断结束
        return true;  // 合并成功
    }  // unite 结束
};  // 并查集类结束

class Solution {  // 题解类
public:  // 公有成员
    int maxActivated(vector<vector<int>>& points) {  // 返回添加一个点后能激活的最大点数
        UnionFind uf;  // 建立并查集
        long long m = (long long) 3e9;  // 大偏移量，用来把 y 坐标平移到与 x 坐标不同的取值区间

        for (auto& p : points) {  // 遍历每个点
            uf.unite(p[0], p[1] + m);  // 把横坐标与「平移后的纵坐标」连成一条边
        }  // 建图结束

        unordered_map<long long, int> cnt;  // 统计每个连通分量包含的点数
        for (auto& p : points) {  // 再次遍历每个点
            long long root = uf.find(p[0]);  // 该点所属连通分量的根
            cnt[root]++;  // 该分量点数加一
        }  // 统计结束

        int mx1 = 0, mx2 = 0;  // mx1 为最大分量，mx2 为次大分量
        for (auto& [_, x] : cnt) {  // 遍历所有分量大小
            if (mx1 < x) {  // 出现新的最大分量
                mx2 = mx1;  // 原最大值降为次大值
                mx1 = x;  // 更新最大值
            } else if (mx2 < x) {  // 没超过最大值但超过次大值
                mx2 = x;  // 更新次大值
            }  // 大小比较结束
        }  // 遍历结束

        return mx1 + mx2 + 1;  // 新增点把两个最大分量连起来，再加上新增点本身
    }  // 方法结束
};  // 类结束
