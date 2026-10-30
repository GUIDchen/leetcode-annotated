// 题目：778. 水位上升的泳池中游泳（Swim in Rising Water）
// 思路：把时间 t 看成水位，用并查集模拟「由低到高淹没格子」：第 t 秒只淹没高度恰为 t 的格子并把它与已淹没的四邻合并，起点与终点一旦连通，当前 t 就是最小可行水位。
// 时间复杂度：O(n^2·α(n^2))，每个格子只被淹没一次、只合并 4 次；空间复杂度：O(n^2)，并查集与高度索引各 n^2。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int swimInWater(vector<vector<int>>& grid) {  // grid：高度矩阵，grid[i][j] 是格子 (i,j) 的深度；返回能游到终点所需的最小时间
        int n = grid.size();  // n：矩阵边长（题目给定 n×n）
        int m = n * n;  // m：格子总数，也是可能的最大时间（高度是 0..m-1 的排列）
        vector<int> p(m);  // p：并查集父指针，下标是格子的线性编号 i*n+j
        iota(p.begin(), p.end(), 0);  // 初始化 p[k]=k，让每个格子各自成为一个集合

        auto find = [&](this auto&& find, int x) -> int {  // 递归 lambda：带路径压缩的 find，用 C++23 的 this auto&& 让 lambda 能调用自身
            if (p[x] != x) {  // p[x] != x 说明 x 不是根，继续往上找
                p[x] = find(p[x]);  // 递归找到根后直接挂到根上，做路径压缩
            }
            return p[x];  // 返回压缩后的根节点
        };

        vector<int> hi(m);  // hi：按高度存格子编号（h → i*n+j），高度 0..m-1 各出现一次
        for (int i = 0; i < n; ++i) {  // 枚举行 i
            for (int j = 0; j < n; ++j) {  // 枚举列 j
                hi[grid[i][j]] = i * n + j;  // 把高度为 grid[i][j] 的格子记下来，便于按时间从小到大淹没
            }
        }

        array<int, 5> dirs{-1, 0, 1, 0, -1};  // 四方向偏移量：读成 (dirs[k], dirs[k+1]) 就是上下左右，末尾多一个 -1 用于收尾

        for (int t = 0; t < m; ++t) {  // 水位 t 从 0 开始逐秒上升，直到起点与终点在中途连通
            int id = hi[t];  // 取高度恰为 t 的格子：它在第 t 秒刚被水淹没
            int x = id / n, y = id % n;  // 把线性编号还原成行列坐标
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int nx = x + dirs[k], ny = y + dirs[k + 1];  // 由偏移量算出邻居坐标
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] <= t) {  // 邻居越界则跳过；邻居高度大于 t 说明还没被淹，水过不去
                    int a = find(x * n + y);  // 当前格子的根（此时该格已被淹没）
                    int b = find(nx * n + ny);  // 邻居格子的根
                    p[a] = b;  // 合并两个集合：连通后水可以从当前格子流到邻居
                }
            }
            if (find(0) == find(m - 1)) {  // 起点 0 与终点 m-1 已经在同一集合，说明本水位就能游到终点
                return t;  // 当前 t 即最小可行水位，直接返回
            }
        }
        return 0;  // 兜底返回：t=m-1 时全图必然连通，正常不会执行到这里
    }  // swimInWater 方法结束
};  // Solution 类定义结束
