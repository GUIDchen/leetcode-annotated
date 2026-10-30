// 题目：695. 岛屿的最大面积（Max Area of Island）
// 思路：把网格看成图，遇到未被标记的陆地就做一次 DFS，把连通的 1 全部改成 0 并累加面积，所有连通块面积的最大值就是答案。
// 时间复杂度：O(m * n)，每个格子最多被访问一次；空间复杂度：O(m * n)，最坏情况下递归栈深度等于整片陆地的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxAreaOfIsland(vector<vector<int>>& grid) {  // grid 中 0 是海水、1 是陆地，返回最大岛屿面积
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数，供边界判断使用
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成 (dx, dy)，依次表示上、右、下、左
        int ans = 0;  // 保存目前为止找到的最大岛屿面积
        function<int(int, int)> dfs = [&](int i, int j) {  // 递归函数：返回从 (i, j) 出发能吞并的陆地面积
            if (grid[i][j] == 0) {  // 当前位置是海水，或已被访问过而被标记为 0
                return 0;  // 这里没有陆地，面积贡献为 0
            }
            int ans = 1;  // 当前格子本身算作 1 个单位面积
            grid[i][j] = 0;  // 立刻标记为已访问，防止重复统计和无限递归
            for (int k = 0; k < 4; ++k) {  // 枚举上下左右四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 由方向数组算出相邻格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n) {  // 只有坐标未越界才继续扩展
                    ans += dfs(x, y);  // 累加该方向上连通陆地的面积
                }
            }
            return ans;  // 返回这一整块连通陆地的面积
        };
        for (int i = 0; i < m; ++i) {  // 逐行扫描所有格子
            for (int j = 0; j < n; ++j) {  // 逐列扫描所有格子
                ans = max(ans, dfs(i, j));  // 每个格子都试着扩展一次，用更大的面积更新答案
            }
        }
        return ans;  // 返回全局最大的岛屿面积
    }
};
