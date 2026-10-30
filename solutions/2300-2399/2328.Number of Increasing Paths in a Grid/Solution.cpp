// 题目：2328. 网格图中递增路径的数目（Number of Increasing Paths in a Grid）
// 思路：把每个格子当作路径终点，用记忆化 DFS 求「从该格出发、只走向严格更大邻居」的路径条数，
//       单格自身算 1 条，四方向累加并取模，再对所有起点求和；时间 O(m×n)，空间 O(m×n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPaths(vector<vector<int>>& grid) {  // grid 是 m×n 的输入矩阵
        const int mod = 1e9 + 7;  // 结果取模的常量
        int m = grid.size(), n = grid[0].size();  // 矩阵的行数与列数
        int f[m][n];  // 记忆化数组：f[i][j] 存从 (i, j) 出发的递增路径条数（变长数组，依赖 gnu 扩展）
        memset(f, 0, sizeof(f));  // 全部清零表示“尚未计算”，0 同时充当未访问标记
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 递归 lambda：返回从 (i, j) 出发的递增路径条数，[&] 按引用捕获外部变量
            if (f[i][j]) {  // 该状态已经算过
                return f[i][j];  // 直接返回缓存值，避免重复递归
            }  // 已计算分支结束
            int ans = 1;  // 单格自身也算一条路径，作为累加初值
            int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向的增量，末尾补 0 便于用 dirs[k] 与 dirs[k+1] 一次取行列增量
            for (int k = 0; k < 4; ++k) {  // 枚举上、右、下、左四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && grid[i][j] < grid[x][y]) {  // 邻居不越界，且数值严格更大才能继续走（保证路径递增）
                    ans = (ans + dfs(x, y)) % mod;  // 以邻居为起点的路径都能接在当前步之后，累加并取模
                }  // 合法邻居分支结束
            }  // 四个方向枚举结束
            return f[i][j] = ans;  // 先写入记忆化数组再返回，后续同状态直接命中缓存
        };  // lambda 定义结束
        int ans = 0;  // 答案：所有格子作为起点的路径总数
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                ans = (ans + dfs(i, j)) % mod;  // 累加以 (i, j) 为起点的路径条数并取模
            }  // 列循环结束
        }  // 行循环结束
        return ans;  // 返回总数
    }  // 方法结束
};  // 类定义结束
