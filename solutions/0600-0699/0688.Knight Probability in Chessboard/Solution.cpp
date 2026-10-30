// 题目：688. 骑士在棋盘上的概率（Knight Probability in Chessboard）
// 思路：概率 DP。f[h][i][j] 表示从 (i, j) 出发走 h 步后仍在棋盘内的概率，倒推：8 个方向能落回棋盘的概率各取 1/8 累加。
// 时间复杂度：O(k·n²·8) = O(k·n²)；空间复杂度：O(k·n²)，保存 k+1 层棋盘状态。
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {  // n 为棋盘边长，k 为移动步数，(row, column) 为骑士起点
        double f[k + 1][n][n];  // DP 表：f[h][i][j] 表示在 (i, j) 走 h 步后仍留在棋盘内的概率
        memset(f, 0, sizeof(f));  // 把整张 DP 表清零，避免未定义值参与累加
        for (int i = 0; i < n; ++i) {  // 枚举起点所在行
            for (int j = 0; j < n; ++j) {  // 枚举起点所在列
                f[0][i][j] = 1;  // 走 0 步一定还在棋盘内，概率为 1，作为 DP 边界
            }
        }
        int dirs[9] = {-2, -1, 2, 1, -2, 1, 2, -1, -2};  // 8 个「马走日」方向的偏移，按 (dx, dy) 相邻成对存放，末尾多一个 -2 便于环形配对
        for (int h = 1; h <= k; ++h) {  // 按步数从小到大递推
            for (int i = 0; i < n; ++i) {  // 枚举当前位置的行 i
                for (int j = 0; j < n; ++j) {  // 枚举当前位置的列 j
                    for (int p = 0; p < 8; ++p) {  // 枚举 8 个可能的来向；dirs[p] 与 dirs[p+1] 组成一个方向
                        int x = i + dirs[p], y = j + dirs[p + 1];  // x、y 为上一步所在位置（从 x,y 走一步到达 i,j）
                        if (x >= 0 && x < n && y >= 0 && y < n) {  // 只有上一步落在棋盘内才是合法来源
                            f[h][i][j] += f[h - 1][x][y] / 8;  // 该来向各占 1/8 概率，把上一步的概率除以 8 后累加到当前状态
                        }
                    }
                }
            }
        }
        return f[k][row][column];  // 返回从起点出发走满 k 步仍留在棋盘内的概率
    }
};