// 题目：1219. 黄金矿工（Path with Maximum Gold）
// 思路：枚举每个非空格子作为起点做 DFS 回溯，进入时把格子清零防止重复采矿，四个方向取最大收益后恢复现场。
// 时间复杂度：最坏 O(m*n*4^(m*n))，相当于枚举所有简单路径；空间复杂度：O(m*n)，递归深度与网格修改。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getMaximumGold(vector<vector<int>>& grid) {  // grid：矿网格，0 表示该格没有金子、不可停留
        int m = grid.size(), n = grid[0].size();  // 行列数，DFS 里用来判断是否越界
        function<int(int, int)> dfs = [&](int i, int j) {  // 用 std::function 定义递归 lambda，按引用捕获外部变量以便读写网格
            if (i < 0 || i >= m || j < 0 || j >= n || !grid[i][j]) {  // 越界，或者该格没有金子（0 同时充当已访问标记），都无法继续采矿
                return 0;  // 该方向收益为 0，直接返回
            }  // 递归出口结束
            int v = grid[i][j];  // 先记住当前格子的金子数，稍后要恢复现场
            grid[i][j] = 0;  // 置 0 表示本路径已经访问过，避免同一条路径重复拿同一格的金子
            int ans = v + max({dfs(i - 1, j), dfs(i + 1, j), dfs(i, j - 1), dfs(i, j + 1)});  // 四个方向继续挖的最大收益，加上当前格的金子
            grid[i][j] = v;  // 回溯：恢复格子的原始值，供其他路径作为起点时使用
            return ans;  // 返回从 (i,j) 出发能挖到的最大金子数
        };  // 递归 lambda 定义结束
        int ans = 0;  // 记录所有起点中的最大收益
        for (int i = 0; i < m; ++i) {  // 枚举每一行作为起点
            for (int j = 0; j < n; ++j) {  // 枚举每一列作为起点
                ans = max(ans, dfs(i, j));  // 用从 (i,j) 出发的收益更新答案
            }  // 列枚举结束
        }  // 行枚举结束
        return ans;  // 返回全局最大收益
    }  // 方法结束
};  // 类定义结束