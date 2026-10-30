// 题目：980. 不同路径 III（Unique Paths III）
// 思路：先统计空格子个数 cnt，再从起点开始回溯 DFS，每走一格计数 +1，走到终点时若恰好走满全部空格即记一条合法路径。
// 时间复杂度：O(m*n*4^(m*n))，回溯会穷举所有简单路径；空间复杂度：O(m*n)，vis 数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int uniquePathsIII(vector<vector<int>>& grid) {  // grid：-1 为障碍、1 为起点、2 为终点、0 为必须经过的空格
        int m = grid.size(), n = grid[0].size();  // m、n 分别是网格的行数与列数
        int cnt = 0;  // cnt 用来统计空格（必须走过的格子）的个数
        for (auto& row : grid) {  // 逐行遍历网格
            for (auto& x : row) {  // 逐列遍历当前行
                cnt += x == 0;  // 值为 0 说明是空格，计入必经格子数（布尔结果参与加法）
            }  // 当前行遍历结束
        }  // 整个网格遍历结束
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成一个方向向量，共上下左右四个方向
        bool vis[m][n];  // vis 记录当前路径上已经走过的格子，防止重复经过
        memset(vis, false, sizeof vis);  // 把所有格子初始化为未访问
        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {  // 递归 lambda：i、j 是当前坐标，k 是已走的步数
            if (grid[i][j] == 2) {  // 走到终点 2
                return k == cnt + 1 ? 1 : 0;  // 步数等于空格数 + 1（终点那一步）才是一条合法路径，转成 0/1 累加
            }  // 终点分支结束
            int ans = 0;  // ans 累计从当前格子出发的合法路径数
            for (int h = 0; h < 4; ++h) {  // 枚举四个方向
                int x = i + dirs[h], y = j + dirs[h + 1];  // 按方向向量算出相邻格子坐标
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1) {  // 边界内、未访问、且不是障碍 -1 才可以走
                    vis[x][y] = true;  // 标记进入该格子
                    ans += dfs(x, y, k + 1);  // 递归统计后续路径数，步数加一
                    vis[x][y] = false;  // 回溯：撤销访问标记，让别的路径还能经过这里
                }  // if 结束
            }  // 方向循环结束
            return ans;  // 返回从当前格子出发的方案数
        };  // lambda 定义结束
        for (int i = 0; i < m; ++i) {  // 逐行寻找起点
            for (int j = 0; j < n; ++j) {  // 逐列寻找起点
                if (grid[i][j] == 1) {  // 值为 1 的格子就是起点
                    vis[i][j] = true;  // 起点本身标记为已访问
                    return dfs(i, j, 0);  // 从起点开始回溯，初始步数为 0
                }  // if 结束
            }  // 内层循环结束
        }  // 外层循环结束
        return 0;  // 没有起点时返回 0（题目保证有起点，属于兜底）
    }  // 方法结束
};  // 类定义结束