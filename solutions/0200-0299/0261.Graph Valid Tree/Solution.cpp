// 题目：261. 以图判树（Graph Valid Tree）
// 思路：并查集（路径压缩）。n 个点构成的树必须连通且无环：逐条边合并端点，若两端点已经同根说明出现环；每合并一次把 n 减一，最后 n == 1 即为树。
// 时间复杂度：O(n α(n))，α 为反阿克曼函数，近似线性；空间复杂度：O(n)，父数组 p。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validTree(int n, vector<vector<int>>& edges) {  // n：节点个数；edges：无向边列表
        vector<int> p(n);  // 并查集的父数组，p[x] 表示 x 的父亲
        iota(p.begin(), p.end(), 0);  // 初始时每个节点自成一个集合，父亲就是自己
        function<int(int)> find = [&](int x) {  // 递归查找根节点，并顺路做路径压缩
            if (p[x] != x) {  // 当前节点不是根
                p[x] = find(p[x]);  // 递归找到根，并让 p[x] 直接指向根
            }
            return p[x];  // 返回所在集合的根
        };  // 结束查找 lambda 的定义
        for (auto& e : edges) {  // 逐条边尝试合并两个端点
            int pa = find(e[0]), pb = find(e[1]);  // 分别求出两个端点所在集合的根
            if (pa == pb) {  // 两端点已经连通
                return false;  // 再加入这条边必然成环，不可能是树
            }
            p[pa] = pb;  // 合并两个集合：让 pa 的根指向 pb 的根
            --n;  // 每成功合并一次，连通分量数减一
        }
        return n == 1;  // 最终只剩一个连通分量才是树（同时保证边数恰为 n-1）
    }  // 结束方法
};  // 结束类