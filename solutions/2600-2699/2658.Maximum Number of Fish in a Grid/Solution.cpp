// 题目：2658. 网格图中鱼的最大数目（Maximum Number of Fish in a Grid）
// 核心思路：把非 0 格子看成水域，用 DFS 求每个连通块的鱼数之和，访问后置 0 标记，取所有连通块的最大值。
// 时间复杂度：O(m*n)，每个格子最多访问一次；空间复杂度：O(m*n)，递归栈最坏深度。
class Solution {  // 题解类
public:  // 方法对外可见
    int findMaxFish(vector<vector<int>>& grid) {  // grid：渔网网格，值为鱼的数量，0 表示陆地；返回一次能捕到的最大鱼数
        int m = grid.size(), n = grid[0].size();  // m 行 n 列
        int ans = 0;  // 记录所有连通水域中能捕到的最大鱼数
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 定义递归 lambda：求 (i, j) 所在连通块的鱼总数
            int cnt = grid[i][j];  // 先收下当前格子的鱼
            grid[i][j] = 0;  // 置 0 表示已访问，避免重复统计与无限递归
            int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项配对得到上下左右四个方向
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 计算相邻格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y]) {  // 未越界且是水域（鱼数大于 0）
                    cnt += dfs(x, y);  // 递归累加该方向连通块的鱼数
                }  // 方向循环结束
            }  // if 分支结束
            return cnt;  // 返回整个连通块的鱼总数
        };  // dfs lambda 定义结束
        for (int i = 0; i < m; ++i) {  // 枚举每一行
            for (int j = 0; j < n; ++j) {  // 枚举每一列
                if (grid[i][j]) {  // 是尚未访问过的水域，说明发现了新的连通块
                    ans = max(ans, dfs(i, j));  // 用该连通块的鱼数更新最大值
                }  // if 分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回最大鱼数
    }
};  // class Solution 结束