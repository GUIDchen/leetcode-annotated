// 题目：1020. 飞地的数量（Number of Enclaves）
// 思路：从四条边界上的所有陆地出发做 DFS，把能到达边界的陆地全部改写成 0；剩下的陆地就是走不出边界的飞地。
// 时间复杂度：O(m * n)，每个格子最多被访问一次；空间复杂度：O(m * n)，最坏情况下 DFS 递归深度达到格子总数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numEnclaves(vector<vector<int>>& grid) {  // grid：0/1 矩阵，1 表示陆地、0 表示海域；返回无法走到边界的陆地格子数
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数；题目保证 grid 非空，所以 grid[0] 一定存在
        const int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成 (dx, dy)，依次覆盖上、右、下、左四个方向
        function<void(int, int)> dfs = [&](int i, int j) {  // 定义递归 lambda：把与 (i, j) 连通的陆地整块「沉没」；[&] 需要按引用捕获 grid、m、n、dirs
            grid[i][j] = 0;  // 先把自己改成 0（标记已访问），避免重复搜索导致死循环
            for (int k = 0; k < 4; ++k) {  // 依次尝试四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居坐标：dirs[k] 是行偏移，dirs[k+1] 是列偏移
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {  // 先判断越界，再判断邻居确实是尚未访问的陆地
                    dfs(x, y);  // 递归处理连通块里的这个邻居
                }
            }
        };
        // 第一步：从上下两条横向边界上的陆地出发，清掉所有能连通到边界的陆地
        for (int j = 0; j < n; ++j) {  // 逐列扫描
            for (int i : {0, m - 1}) {  // 同时处理上边界（第 0 行）与下边界（第 m - 1 行）
                if (grid[i][j] == 1) {  // 该边界格子是陆地才从这里开始搜索
                    dfs(i, j);  // 从边界出发淹没整块连通的陆地，它们都能走出边界
                }
            }
        }
        // 第二步：同理处理最左列与最右列上的陆地
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j : {0, n - 1}) {  // 同时处理左边界（第 0 列）与右边界（第 n - 1 列）
                if (grid[i][j] == 1) {  // 该边界格子是陆地才从这里开始搜索
                    dfs(i, j);  // 从边界出发淹没整块连通的陆地
                }
            }
        }
        // 此时剩下的 1 都是四周被海域围住、走不到边界的飞地
        int ans = 0;  // 统计剩余陆地数量
        for (const auto& row : grid) {  // 逐行累加
            ans += accumulate(row.begin(), row.end(), 0);  // accumulate 对整行求和，初值为 0
        }
        // 所有剩余陆地都是飞地，直接返回总数
        return ans;  // 返回飞地格子数
    }
};
