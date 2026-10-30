// 题目：2852. 所有单元格的远离程度之和（Sum of Remoteness of All Cells）
// 核心思路：DFS 求每个连通块的石头总和 s 与格子数 t，块内每个格子对外只能到达其它块的 cnt - t 个格子，贡献 (cnt - t) * s。
// 时间复杂度：O(n^2)，每个格子只被访问一次；空间复杂度：O(n^2)，递归栈最深 n^2。
class Solution {  // LeetCode 约定的题解类
public:  // 对外公开的接口区域
    long long sumRemoteness(vector<vector<int>>& grid) {  // grid 为 n x n 网格，-1 表示障碍，正数表示该格石头数
        using pli = pair<long long, int>;  // 自定义返回类型：第一个是石头总和，第二个是格子数
        int n = grid.size();  // 网格边长
        int cnt = 0;  // cnt 统计可通行（石头数大于 0）的格子总数
        for (auto& row : grid) {  // 遍历每一行
            for (int x : row) {  // 遍历行内每一格
                cnt += x > 0;  // x > 0 表示可通行，布尔值累加到计数里
            }  // 结束 for 循环
        }  // 结束 for 循环
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组，相邻两项构成一个方向向量
        function<pli(int, int)> dfs = [&](int i, int j) {  // 递归 lambda 做 flood fill，返回该连通块的 (石头总和, 格子数)
            long long s = grid[i][j];  // 当前格的石头数作为连通块和的初值
            int t = 1;  // 格子数从 1 开始
            grid[i][j] = 0;  // 清零相当于打上已访问标记，避免回头
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居坐标
                if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] > 0) {  // 邻居在界内且可通行才继续深入
                    auto [ss, tt] = dfs(x, y);  // 递归统计邻居所在的同一连通块
                    s += ss;  // 累加石头数
                    t += tt;  // 累加格子数
                }  // 结束 if 分支
            }  // 结束 for 循环
            return pli(s, t);  // 返回本连通块的统计结果
        };  // lambda 定义结束
        long long ans = 0;  // 远离程度之和，用 long long 防溢出
        for (int i = 0; i < n; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                if (grid[i][j] > 0) {  // 只从尚未访问的格子发起一次连通块搜索
                    auto [s, t] = dfs(i, j);  // 得到该连通块的石头总和 s 与格子数 t
                    ans += (cnt - t) * s;  // 块内每个格子能到达 cnt - t 个格子，故总贡献为 (cnt - t) * s
                }  // 结束 if 分支
            }  // 结束 for 循环
        }  // 结束 for 循环
        return ans;  // 返回累加结果
    }  // 结束函数体
};  // 结束类定义