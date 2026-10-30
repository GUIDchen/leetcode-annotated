// 3608. 包含 K 个连通分量需要的最小时间 / Minimum Time for K Connected Components
// 核心思路：把边按权重升序排序后从最大权重端反向遍历，用并查集逐条“加入”边；连通分量数首次降到 k 以下时，当前边的权重就是答案（权重不超过它的边都可保留）。
// 复杂度：时间 O(e log e)（排序主导），空间 O(n)；e 为边数、n 为节点数。
class UnionFind {  // 并查集：按大小合并维护连通块
public:  // 公有数据部分
    vector<int> p;  // 父节点数组
    vector<int> size;  // 块大小数组

    UnionFind(int n) {  // 构造函数：n 个节点各自独立成块
        p.resize(n);  // 父节点数组开到 n
        size.resize(n, 1);  // 块大小全部初始化为 1
        for (int i = 0; i < n; i++) {  // 逐节点初始化
            p[i] = i;  // 每个节点的父节点先指向自己
        }  // 初始化循环结束
    }  // 构造函数结束

    int find(int x) {  // 查找所在连通块的根，并做路径压缩
        if (p[x] != x) {  // 当前节点不是根
            p[x] = find(p[x]);  // 递归找根，并把当前节点直接挂到根上
        }  // 条件分支结束
        return p[x];  // 返回根编号
    }  // 查找函数结束

    bool unite(int a, int b) {  // 合并两个节点所在的连通块
        int pa = find(a);  // 先找到第一个节点的根
        int pb = find(b);  // 再找到第二个节点的根
        if (pa == pb) {  // 本来就在同一块里，无需合并
            return false;  // 返回合并失败
        }  // 分支结束

        if (size[pa] > size[pb]) {  // 把较小的块挂到较大的块下面
            p[pb] = pa;  // 小编号块指向大编号块
            size[pa] += size[pb];  // 合并后更新大块的规模
        } else {  // 否则反过来挂
            p[pa] = pb;  // 大编号块指向小编号块
            size[pb] += size[pa];  // 合并后更新大块的规模
        }  // 分支结束
        return true;  // 返回合并成功
    }  // 合并函数结束
};  // 并查集类定义结束

class Solution {  // 题解类
public:  // 公有接口部分
    int minTime(int n, vector<vector<int>>& edges, int k) {  // 主函数：n 个节点、edges 为带权边、k 为目标连通分量数
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {  // 按边的权重升序排序
            return a[2] < b[2];  // 以小权重为先的比较规则
        });  // 排序调用结束

        UnionFind uf(n);  // 初始化并查集，且每个节点自成一个分量
        int cnt = n;  // 当前连通分量数等于节点数

        for (int i = edges.size() - 1; i >= 0; i--) {  // 从权重最大的边开始反向遍历
            int u = edges[i][0];  // 取出边的左端点
            int v = edges[i][1];  // 取出边的右端点
            int t = edges[i][2];  // 取出这条边的时间权重

            if (uf.unite(u, v)) {  // 只有真正合并了两个分量才算有效连接
                cnt--;  // 连通分量数减一
                if (cnt < k) {  // 分量数首次小于 k
                    return t;  // 当前边的时间即为最小时间
                }  // 分支结束
            }  // 分支结束
        }  // 遍历结束
        return 0;  // 所有边都加入后仍不满足，说明无需任何操作
    }  // 主函数结束
};  // 类定义结束
