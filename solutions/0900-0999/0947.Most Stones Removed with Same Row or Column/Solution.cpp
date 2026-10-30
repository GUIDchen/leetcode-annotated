// 题目：947. 移除最多的同行或同列石头（Most Stones Removed with Same Row or Column）
// 思路：把每块石头看作一个点，同行或同列就属于同一个连通块；用并查集合并相邻石头，成功合并的次数就是最多能移除的石头数。
// 时间复杂度：O(n^2·α(n))，两两枚举 n 块石头，并查集近似 O(1)；空间复杂度：O(n)，父指针与集合大小数组。
class UnionFind {  // 并查集：维护石头的连通关系，判断两块石头是否已经属于同一块
public:  // 以下接口对外可见
    UnionFind(int n) {  // n：元素个数，这里就是石头数量
        p = vector<int>(n);  // 父指针数组，先按 n 个元素开好空间
        size = vector<int>(n, 1);  // 每个集合的大小，初始各自为 1
        iota(p.begin(), p.end(), 0);  // 初始时每个元素自成一个集合，父指针都指向自己
    }

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回本次是否真的发生了合并
        int pa = find(a), pb = find(b);  // 先找到两个元素各自的根
        if (pa == pb) {  // 根相同说明本来就连通，无需合并
            return false;  // 没有合并，故不计入可移除的石头数
        }
        if (size[pa] > size[pb]) {  // 按集合大小合并：小集合挂到大集合下，保证树高接近对数
            p[pb] = pa;  // 小集合的根指向大集合的根
            size[pa] += size[pb];  // 更新大集合的元素个数
        } else {  // 另一种情况：把 pa 挂到 pb 下面
            p[pa] = pb;  // pa 成为 pb 的子节点
            size[pb] += size[pa];  // 更新 pb 集合的元素个数
        }
        return true;  // 本次合并成功
    }

    int find(int x) {  // 查找 x 所在集合的根，同时做路径压缩
        if (p[x] != x) {  // 还没直接指向根
            p[x] = find(p[x]);  // 递归找根，并把路径上的节点直接挂到根上
        }
        return p[x];  // 返回根节点
    }

private:  // 以下数据仅供内部使用
    vector<int> p, size;  // 父指针数组与集合大小数组
};

class Solution {  // 题解主类
public:  // 题解方法对外可见
    int removeStones(vector<vector<int>>& stones) {  // stones：每个元素的 (行, 列) 坐标
        int n = stones.size();  // 石头数量，同时是并查集的元素个数
        UnionFind uf(n);  // 每块石头最初看作一个独立连通块
        int ans = 0;  // 成功合并的次数，它正好等于最多可移除的石头数
        for (int i = 0; i < n; ++i) {  // 枚举每一块石头作为「新加入者」
            for (int j = 0; j < i; ++j) {  // 只和之前枚举过的石头配对，避免重复比较
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {  // 只有同行或同列的两块石头才可能互相消去
                    ans += uf.unite(i, j);  // 合并成功说明多出一条冗余边，即可多移除一块石头
                }
            }
        }
        return ans;  // 每个连通块最后必然剩下一块石头，其余都已移除
    }
};