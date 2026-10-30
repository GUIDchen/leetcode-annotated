// 题目：1579. 保证图可完全遍历（Remove Max Number of Edges to Keep Graph Fully Traversable）
// 思路：并查集贪心。先尽量用两人共用的 type 3 边同时连通两棵树（一条边收益双倍），再分别用 type 1 / type 2 边补连通；合并失败的边都是可删除的冗余边。
// 时间复杂度：O(E * α(n))，每条边做常数次并查集操作；空间复杂度：O(n)，两个并查集各存父指针与集合大小。
class UnionFind {  // 并查集：维护连通分量个数，支持合并与冗余判断
public:  // 对外接口
    int cnt;  // 当前连通分量个数，初始为 n

    UnionFind(int n) {  // 构造：n 个节点各自独立
        p = vector<int>(n);  // 父指针数组，先只分配空间
        size = vector<int>(n, 1);  // 按大小合并用的 size 数组，每个分量初始大小为 1
        iota(p.begin(), p.end(), 0);  // iota 把父指针填成 0..n-1，即每个节点自成一个集合
        cnt = n;  // 初始共有 n 个连通分量
    }  // 构造结束

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回是否真的发生了合并（节点编号从 1 开始）
        int pa = find(a - 1), pb = find(b - 1);  // 先求两个根，注意编号是 1 基的，需要减 1 转成下标
        if (pa == pb) {  // 根相同说明已经连通，这条边是多余的
            return false;  // 返回 false 表示没有合并
        }  // if 分支结束
        if (size[pa] > size[pb]) {  // 按集合大小决定挂接方向，避免树退化成链
            p[pb] = pa;  // 小集合挂到大集合下面
            size[pa] += size[pb];  // 大集合大小累加
        } else {  // 对称情况
            p[pa] = pb;  // 把小根挂到大根下面
            size[pb] += size[pa];  // 更新大根的大小
        }  // else 分支结束
        --cnt;  // 少了一个连通分量
        return true;  // 合并成功
    }  // unite 结束

    int find(int x) {  // 带路径压缩的查找
        if (p[x] != x) {  // 父指针不等于自己说明还没到根
            p[x] = find(p[x]);  // 递归压缩：把路径上所有节点直接指向根
        }  // if 分支结束
        return p[x];  // 返回根下标
    }  // find 结束

private:  // 私有成员
    vector<int> p, size;  // 父指针与集合大小
};  // 并查集类结束

class Solution {  // 题解类
public:  // 题解方法对外可见
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {  // n：节点数；edges：每条边为 [type,u,v]，type 1 仅 Alice、2 仅 Bob、3 两人共用
        UnionFind ufa(n);  // Alice 的并查集
        UnionFind ufb(n);  // Bob 的并查集
        int ans = 0;  // 记录可以删掉的边数
        for (auto& e : edges) {  // 第一轮：先处理两人共用的 type 3 边，一条边能同时连通两棵树，收益最高
            int t = e[0], u = e[1], v = e[2];  // 取出边的类型与两个端点
            if (t == 3) {  // type 3 表示两人都能走的共用边
                if (ufa.unite(u, v)) {  // Alice 侧合并成功才需要让 Bob 侧也合并
                    ufb.unite(u, v);  // Bob 侧做同样的合并，共用边对两边同时生效
                } else {  // 否则说明这条边对 Alice 已经冗余
                    ++ans;  // 直接删掉，计数加一
                }  // if 分支结束
            }  // type 判断结束
        }  // 第一轮结束
        for (auto& e : edges) {  // 第二轮：处理只属于一方的 type 1 / type 2 边
            int t = e[0], u = e[1], v = e[2];  // 再次取出边的类型与两个端点
            ans += t == 1 && !ufa.unite(u, v);  // Alice 专用边：合并失败说明多余，ans 自增
            ans += t == 2 && !ufb.unite(u, v);  // Bob 专用边：同理统计多余的边
        }  // 第二轮结束
        return ufa.cnt == 1 && ufb.cnt == 1 ? ans : -1;  // 两张图都必须连通（分量数都为 1），否则无解返回 -1
    }  // 方法结束
};  // 题解类结束