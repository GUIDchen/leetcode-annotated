// 3651. 带传送的最小路径成本（Minimum Cost Path with Teleportations）
// 核心思路：f[t][i][j] 表示至多用 t 次传送到达 (i,j) 的最小成本；传送免费但要求目标格子的值不大于出发格子的值，故按格子值从大到小维护 f[t-1] 的前缀最小值即可完成一次传送，再对每层做一次向右/向下的网格 DP。
// 复杂度：时间 O(k·m·n + m·n·log(m·n))，空间 O(k·m·n)，其中 m、n 为矩阵行列数。
class Solution {  // 定义题解类
public:  // 公有接口
    int minCost(vector<vector<int>>& grid, int k) {  // 返回从 (0,0) 到 (m-1,n-1) 的最小总成本，最多可免费传送 k 次
        int m = grid.size(), n = grid[0].size();  // 矩阵的行数与列数
        int inf = INT_MAX / 2;  // 取 INT_MAX 的一半作为无穷大，防止加法溢出

        vector<vector<vector<int>>> f(k + 1, vector<vector<int>>(m, vector<int>(n, inf)));  // f[t][i][j]：至多使用 t 次传送到达 (i,j) 的最小成本

        f[0][0][0] = 0;  // 不使用传送时，起点成本为 0
        for (int i = 0; i < m; i++) {  // 第一遍：只允许向右、向下走，做一次网格前缀 DP
            for (int j = 0; j < n; j++) {  // 枚举列
                if (i > 0) {  // 能从上方走来
                    f[0][i][j] = min(f[0][i][j], f[0][i - 1][j] + grid[i][j]);  // 由上方格子的成本加上当前格子的值转移
                }  // 上方转移结束
                if (j > 0) {  // 能从左方走来
                    f[0][i][j] = min(f[0][i][j], f[0][i][j - 1] + grid[i][j]);  // 由左方格子的成本加上当前格子的值转移
                }  // 左方转移结束
            }  // 列循环结束
        }  // 行循环结束

        unordered_map<int, vector<pair<int, int>>> g;  // 按格子的值分组：g[x] 保存所有值等于 x 的格子坐标
        for (int i = 0; i < m; i++) {  // 枚举行
            for (int j = 0; j < n; j++) {  // 枚举列
                int x = grid[i][j];  // 当前格子的值
                g[x].push_back({i, j});  // 把该坐标加入对应值的分组
            }  // 列循环结束
        }  // 行循环结束

        vector<int> keys;  // keys 保存矩阵中出现过的所有不同值
        keys.reserve(g.size());  // 预留容量，避免反复扩容
        for (auto& e : g) {  // 遍历哈希表中的每个分组
            keys.push_back(e.first);  // 记录该分组对应的值
        }  // 分组遍历结束
        sort(keys.begin(), keys.end(), greater<int>());  // 按值从大到小排序，便于用前缀最小值完成传送转移

        for (int t = 1; t <= k; t++) {  // 枚举传送次数，从 1 次到 k 次
            int mn = inf;  // mn 记录「值不小于当前处理值」的格子中 f[t-1] 的最小值
            for (int key : keys) {  // 按值从大到小遍历分组
                auto& pos = g[key];  // 取出当前值对应的所有格子坐标
                for (auto& p : pos) {  // 先把当前值这一组的 f[t-1] 也并入 mn
                    mn = min(mn, f[t - 1][p.first][p.second]);  // 更新前缀最小值
                }  // 本组统计结束
                for (auto& p : pos) {  // 再把 mn 赋给当前值的每个格子：可以从值不小于它的格子免费传送过来
                    f[t][p.first][p.second] = mn;  // 传送后的成本即为前缀最小值
                }  // 本组赋值结束
            }  // 分组遍历结束
            for (int i = 0; i < m; i++) {  // 传送之后还要允许继续向右、向下走，再做一次网格 DP 松弛
                for (int j = 0; j < n; j++) {  // 枚举列
                    if (i > 0) {  // 能从上方走来
                        f[t][i][j] = min(f[t][i][j], f[t][i - 1][j] + grid[i][j]);  // 由上方格子的成本加上当前格子的值转移
                    }  // 上方转移结束
                    if (j > 0) {  // 能从左方走来
                        f[t][i][j] = min(f[t][i][j], f[t][i][j - 1] + grid[i][j]);  // 由左方格子的成本加上当前格子的值转移
                    }  // 左方转移结束
                }  // 列循环结束
            }  // 行循环结束
        }  // 传送次数循环结束

        int ans = inf;  // 答案初始化为无穷大
        for (int t = 0; t <= k; t++) {  // 枚举实际使用的传送次数
            ans = min(ans, f[t][m - 1][n - 1]);  // 取各种传送次数下到达终点的最小值
        }  // 枚举结束
        return ans;  // 返回最小总成本
    }  // minCost 结束
};  // 类定义结束
