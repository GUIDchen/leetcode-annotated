// 题目：2812. 找出最安全路径（Find the Safest Path in a Grid）
// 思路：先从所有小偷格子做多源 BFS，求出每个格子到最近小偷的曼哈顿距离（安全度）；再把格子按安全度从大到小逐个加入并查集，起点与终点第一次连通时的高度就是答案。
// 时间复杂度：O(n^2 log n)，需要对 n^2 个格子排序；空间复杂度：O(n^2)，距离表、排序表与并查集。
class UnionFind {  // 并查集：路径压缩，用于维护「安全度不低于某值」的连通块
public:  // 对外可见
    vector<int> p;  // p[x] 记录 x 的父结点，p[x] == x 说明它是根
    int n;  // n 记录当前连通块个数，unite 成功时自减

    UnionFind(int _n)  // 构造函数：建立 _n 个结点的并查集
        : n(_n)  // 成员初始化列表：先记录结点数
        , p(_n) {  // 再分配父数组，初值随后用 iota 填成 0..n-1
        iota(p.begin(), p.end(), 0);  // iota 依次写入 0,1,2,...，初始时每个结点自成一棵树
    }

    bool unite(int a, int b) {  // 合并 a、b 所在的两个集合，返回是否真的发生了合并
        int pa = find(a), pb = find(b);  // 分别找到两个结点所在树的根
        if (pa == pb) return false;  // 根相同说明已连通，无需合并
        p[pa] = pb;  // 直接把 a 的根挂到 b 的根下面
        --n;  // 连通块个数减一
        return true;  // 报告合并成功
    }

    int find(int x) {  // 查找 x 的根，同时做路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // x 不是根时，递归把路径上的结点直接挂到根上
        return p[x];  // 返回根结点
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumSafenessFactor(vector<vector<int>>& grid) {  // grid：0 表示空地、1 表示小偷；返回起点到终点的最大安全度
        int n = grid.size();  // 网格边长 n（题目保证是 n × n）
        if (grid[0][0] || grid[n - 1][n - 1]) {  // 起点或终点本身有小偷，任何路径的安全度都是 0
            return 0;  // 无法避开，直接返回 0
        }
        queue<pair<int, int>> q;  // BFS 队列，初始装入所有小偷格子（多源）
        int dist[n][n];  // dist[i][j]：格子 (i, j) 到最近小偷的曼哈顿距离
        memset(dist, 0x3f, sizeof(dist));  // 初值取 0x3f3f3f3f（足够大的数），同时充当「未访问」标记
        for (int i = 0; i < n; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (grid[i][j]) {  // 该格子有小偷，作为 BFS 的源点
                    dist[i][j] = 0;  // 小偷格子的安全度为 0
                    q.emplace(i, j);  // 入队，稍后向外扩散
                }
            }
        }
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：配合下标 k、k+1 得到上右下左四个方向的偏移
        while (!q.empty()) {  // 多源 BFS：一层层向外扩散
            auto [i, j] = q.front();  // 取出队首格子，同时解包出行列下标
            q.pop();  // 弹出队首
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 计算相邻格子的坐标
                if (x >= 0 && x < n && y >= 0 && y < n && dist[x][y] == 0x3f3f3f3f) {  // 仍在网格内且尚未被访问（值仍等于初值）才更新
                    dist[x][y] = dist[i][j] + 1;  // 距离等于当前格子的距离加一
                    q.emplace(x, y);  // 新格子入队，继续向外扩散
                }
            }
        }
        vector<tuple<int, int, int>> t;  // 收集每个格子的 (安全度, 行, 列)
        for (int i = 0; i < n; ++i) {  // 逐行遍历
            for (int j = 0; j < n; ++j) {  // 逐列遍历
                t.emplace_back(dist[i][j], i, j);  // tuple 按字典序比较，安全度在第一位，便于整体排序
            }
        }
        sort(t.begin(), t.end());  // 按安全度升序排序
        reverse(t.begin(), t.end());  // 反转成降序，从安全度最高的格子开始处理
        UnionFind uf(n * n);  // 并查集：把二维坐标压成一维编号 i * n + j
        for (auto [d, i, j] : t) {  // 从高到低逐个把格子加入
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格子的坐标
                if (x >= 0 && x < n && y >= 0 && y < n && dist[x][y] >= d) {  // 邻居在网格内，且安全度不低于当前格子，才能连通
                    uf.unite(i * n + j, x * n + y);  // 合并两个格子，形成由高安全度格子组成的连通块
                }
            }
            if (uf.find(0) == uf.find(n * n - 1)) {  // 起点与终点已经连通，说明存在安全度不低于 d 的路径
                return d;  // 由于是按安全度从高到低合并，第一次连通时的高度就是最大安全度
            }
        }
        return 0;  // 理论上的兜底返回（正常流程会提前返回）
    }
};  // 类定义结束