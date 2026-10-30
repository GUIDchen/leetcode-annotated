// 题目：1627. 带阈值的图连通性（Graph Connectivity With Threshold）
// 思路：枚举所有大于 threshold 的公因数 a，把 a 的所有倍数与 a 合并到同一个并查集，最后用根是否相同判断每个询问的连通性。
// 时间复杂度：O(n log n + q·α(n))，调和级数枚举倍数；空间复杂度：O(n)，并查集数组。
class UnionFind {  // 并查集：维护连通分量，支持合并与查询根
public:  // public:
    UnionFind(int n) {  // 构造函数：n 个元素，编号 0..n-1
        p = vector<int>(n);  // p 数组保存每个元素的父节点
        size = vector<int>(n, 1);  // size 保存每个根所在集合的大小，用于按大小合并
        iota(p.begin(), p.end(), 0);  // 每个元素初始自成一个集合，父节点指向自己
    }  // 构造函数结束

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回是否真的发生合并
        int pa = find(a), pb = find(b);  // 先找到两个元素各自所在集合的根
        if (pa == pb) {  // 根相同说明本来就在同一集合
            return false;  // 无需合并，返回 false
        }  // if 分支结束
        if (size[pa] > size[pb]) {  // 按集合大小合并：把较小的集合挂到较大集合下面
            p[pb] = pa;  // b 的根挂到 a 的根下
            size[pa] += size[pb];  // a 集合的大小增加
        } else {  // 否则反过来挂
            p[pa] = pb;  // a 的根挂到 b 的根下
            size[pb] += size[pa];  // b 集合的大小增加
        }  // if 分支结束
        return true;  // 合并成功，返回 true
    }  // unite 结束

    int find(int x) {  // 路径压缩查找：返回 x 所在集合的根
        if (p[x] != x) {  // 父节点不是自己，说明还没到根
            p[x] = find(p[x]);  // 递归找到根，并把路径上的节点直接挂到根上
        }  // if 分支结束
        return p[x];  // 返回根节点
    }  // find 结束

private:  // private:
    vector<int> p, size;  // 父节点数组与集合大小数组
};  // UnionFind 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {  // n 为节点编号上限，threshold 为阈值，queries 为待判断的连通性询问
        UnionFind uf(n + 1);  // 建立 n+1 个元素的并查集（节点编号 1..n）
        for (int a = threshold + 1; a <= n; ++a) {  // 枚举所有大于阈值的数 a，把它当作公因数
            for (int b = a + a; b <= n; b += a) {  // 枚举 a 的所有倍数 b = 2a, 3a, ...
                uf.unite(a, b);  // 公因数 a > threshold，说明 a 与 b 之间有边，合并两个集合
            }  // 倍数循环结束
        }  // 因数循环结束
        vector<bool> ans;  // 保存每个询问的答案
        for (auto& q : queries) {  // 逐个处理询问
            ans.push_back(uf.find(q[0]) == uf.find(q[1]));  // 根相同即连通，把布尔结果加入答案
        }  // 询问循环结束
        return ans;  // 返回所有询问的答案
    }  // 方法结束
};  // 类定义结束