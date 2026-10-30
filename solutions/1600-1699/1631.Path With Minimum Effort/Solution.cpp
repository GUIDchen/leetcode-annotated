// 题目：1631. 最小体力消耗路径（Path With Minimum Effort）
// 思路：把相邻格子的高度差当成边权，按边权从小到大做 Kruskal 连通，起点与终点首次连通时的边权就是最小体力消耗。
// 时间复杂度：O(mn·log(mn))，边数约 2mn，排序主导；空间复杂度：O(mn)，存边表与并查集数组。
class UnionFind {  // 并查集：维护连通分量，支持按大小合并与路径压缩
public:  // 对外接口
    UnionFind(int n) {  // 构造函数：n 个结点，初始各自独立
        p = vector<int>(n);  // p 记录每个结点的父结点
        size = vector<int>(n, 1);  // size 记录每个根的集合大小，用于小集合挂到大集合上
        iota(p.begin(), p.end(), 0);  // iota 把 p 填成 0,1,2,...,n-1，父结点初始指向自己
    }  // 构造函数结束

    bool unite(int a, int b) {  // 合并 a、b 所在集合；返回 false 表示原本已连通
        int pa = find(a), pb = find(b);  // 先找到两个结点各自的根
        if (pa == pb) {  // 根相同说明已在同一集合
            return false;  // 无需合并
        }  // if 结束
        if (size[pa] > size[pb]) {  // 比较集合大小，决定把哪一个根挂到另一个根下
            p[pb] = pa;  // pa 集合更大，把 pb 挂到 pa 下
            size[pa] += size[pb];  // 更新新根 pa 的集合大小
        } else {  // 否则（pb 更大或相等）做反向挂接
            p[pa] = pb;  // 把 pa 挂到 pb 下
            size[pb] += size[pa];  // 更新新根 pb 的集合大小
        }  // if-else 结束
        return true;  // 合并成功
    }  // unite 方法结束

    int find(int x) {  // 查找 x 所在集合的根，路径压缩
        if (p[x] != x) {  // 父结点不是自己，说明还没到根
            p[x] = find(p[x]);  // 递归找根，并把路径上所有结点直接挂到根上（路径压缩）
        }  // if 结束
        return p[x];  // 返回根结点编号（同时也完成了压缩写回）
    }  // find 方法结束

    bool connected(int a, int b) {  // 判断 a、b 是否连通
        return find(a) == find(b);  // 两者根相同即连通
    }  // connected 方法结束

private:  // 以下为私有成员
    vector<int> p, size;  // 父结点数组与集合大小数组
};  // UnionFind 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumEffortPath(vector<vector<int>>& heights) {  // heights 是 m×n 的高度矩阵，返回从左上角到右下角的最小体力消耗
        int m = heights.size(), n = heights[0].size();  // m、n 分别为行数与列数
        vector<array<int, 3>> edges;  // 边表：三元组 {高度差, 起点编号, 终点编号}，结点编号用 i*n+j 压平
        int dirs[3] = {0, 1, 0};  // 方向数组：只需向右 (0,1) 和向下 (1,0) 两个方向，避免重复建边
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                for (int k = 0; k < 2; ++k) {  // 枚举两个前进方向
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 由当前格 (i,j) 与方向得到相邻格 (x,y)
                    if (x >= 0 && x < m && y >= 0 && y < n) {  // 边界检查：相邻格必须仍在矩阵内
                        edges.push_back({abs(heights[i][j] - heights[x][y]), i * n + j, x * n + y});  // 把这条相邻边加入边表，边权就是两格高度差的绝对值
                    }  // if 结束
                }  // 方向循环结束
            }  // 列循环结束
        }  // 行循环结束
        sort(edges.begin(), edges.end());  // 按边权升序排序：Kruskal 从小到大加边
        UnionFind uf(m * n);  // 并查集初始化 mn 个格子结点
        for (auto& [h, a, b] : edges) {  // 依次处理每一条边，h 为高度差，a/b 为两端结点编号
            uf.unite(a, b);  // 把这条边的两个端点所在集合合并
            if (uf.connected(0, m * n - 1)) {  // 检查起点 0 与终点 mn-1 是否已经连通
                return h;  // 首次连通时刚加入的边权 h 就是这条路径上的最大高度差，也是最小体力消耗
            }  // if 结束
        }  // 边循环结束
        return 0;  // 只有 1 个格子（或无需移动）时消耗为 0
    }  // minimumEffortPath 方法结束
};  // 题解类定义结束