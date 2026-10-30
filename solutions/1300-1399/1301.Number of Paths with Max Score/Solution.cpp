// 题目：1301. 最大得分的路径数目（Number of Paths with Max Score）
// 思路：从右下角往左上角做网格 DP，f[i][j] 是到终点的最大得分（-1 表示不可达），g[i][j] 是取到该得分的方案数。
// 时间复杂度：O(n^2)，每个格子只向三个方向转移；空间复杂度：O(n^2)，两个 n×n 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> pathsWithMaxScore(vector<string>& board) {  // board：棋盘，'S' 起点、'E' 终点、'X' 障碍、数字为分数
        int n = board.size();  // 棋盘边长
        const int mod = 1e9 + 7;  // 方案数取模
        int f[n][n];  // f[i][j]：(i,j) 走到终点的最大得分，-1 表示不可达
        int g[n][n];  // g[i][j]：取得最大得分的路径条数
        memset(f, -1, sizeof(f));  // 按字节置 -1，等价于把所有格子初始化为不可达
        memset(g, 0, sizeof(g));  // 方案数全部初始化为 0
        f[n - 1][n - 1] = 0;  // 终点自身得分为 0
        g[n - 1][n - 1] = 1;  // 终点自身算 1 条路径（空路径）

        auto update = [&](int i, int j, int x, int y) {  // 用相邻格子 (x,y) 的结果去更新 (i,j)
            if (x >= n || y >= n || f[x][y] == -1 || board[i][j] == 'X' || board[i][j] == 'S') {  // 越界、后继不可达，或当前格是障碍/起点
                return;  // 不做任何转移
            }
            if (f[x][y] > f[i][j]) {  // 后继给的得分更高，直接替换
                f[i][j] = f[x][y];  // 更新最大得分
                g[i][j] = g[x][y];  // 方案数跟着替换
            } else if (f[x][y] == f[i][j]) {  // 两条路线得分相同，方案数累加
                g[i][j] = (g[i][j] + g[x][y]) % mod;  // 累加后取模防止溢出
            }
        };  // lambda 定义结束，按引用捕获 n、f、g、mod 等外部变量

        for (int i = n - 1; i >= 0; --i) {  // 从最后一行往上推
            for (int j = n - 1; j >= 0; --j) {  // 从最后一列往左推
                update(i, j, i + 1, j);  // 转移到下方格子
                update(i, j, i, j + 1);  // 转移到右方格子
                update(i, j, i + 1, j + 1);  // 转移到右下对角格子
                if (f[i][j] != -1) {  // 该格子可达才需要把自身分数加上去
                    if (board[i][j] >= '0' && board[i][j] <= '9') {  // 数字格才有分数
                        f[i][j] += (board[i][j] - '0');  // 字符转数字并累加
                    }
                }
            }
        }
        vector<int> ans(2);  // 结果：ans[0] 最大得分，ans[1] 方案数（默认都是 0）
        if (f[0][0] != -1) {  // 起点能到达终点
            ans[0] = f[0][0];  // 填入最大得分
            ans[1] = g[0][0];  // 填入方案数
        }
        return ans;  // 起点不可达时 ans 保持 [0, 0]
    }
};