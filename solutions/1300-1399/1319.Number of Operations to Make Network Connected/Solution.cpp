// 题目：1319. 连通网络的操作次数（Number of Operations to Make Network Connected）
// 思路：并查集合并已有连接，统计多余边数 cnt；连通 k 个连通块需 k-1 条边，边够则答案为 k-1，否则 -1。
// 时间复杂度：O(m·α(n))，并查集近似常数；空间复杂度：O(n)，父数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int makeConnected(int n, vector<vector<int>>& connections) {  // n 为计算机数，connections 为已有网线连接，返回最少操作次数
        vector<int> p(n);  // 并查集父数组，p[x] 记录 x 的父节点
        iota(p.begin(), p.end(), 0);  // 初始每个节点自成一类，iota 依次填入 0..n-1
        int cnt = 0;  // cnt 统计多余的边（连在同一连通块上、可挪用重连的网线数）
        function<int(int)> find = [&](int x) -> int {  // 带路径压缩的递归查找函数
            if (p[x] != x) {  // 若当前节点不是根
                p[x] = find(p[x]);  // 递归找到根并直接挂到根上，压缩查询路径
            }  // 非根分支结束
            return p[x];  // 返回当前节点所在连通块的根
        };  // 查找函数定义结束
        for (const auto& c : connections) {  // 逐条处理已有连接
            int pa = find(c[0]), pb = find(c[1]);  // 分别求两个端点所在连通块的根
            if (pa == pb) {  // 两端已连通，说明这条边多余
                ++cnt;  // 多余边数加一
            } else {  // 否则两端属于不同连通块，需要合并
                p[pa] = pb;  // 合并：把一棵树的根挂到另一棵的根上
                --n;  // 合并后连通块数量减一，用 n 记录剩余块数
            }  // 合并分支结束
        }  // 所有连接处理完毕
        return cnt >= n - 1 ? n - 1 : -1;  // 连通 n 个块需 n-1 条边：多余边够用就返回 n-1，否则无法连通返回 -1
    }  // 方法结束
};  // 类定义结束
