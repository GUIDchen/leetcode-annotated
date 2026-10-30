// 题目：1958. 检查操作是否合法（Check if Move is Legal）
// 思路：落子后沿八个方向分别探测，若某个方向上先遇到对方棋子、再遇到我方棋子（中间至少一枚对方棋子），则该方向可夹子，操作合法。
// 时间复杂度：O(1)，只有 8 个方向、每方向最多走 6 步；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color) {  // board 为 8×8 棋盘，rMove/cMove 是落子位置，color 是落子方颜色（'B' 或 'W'）
        for (int a = -1; a <= 1; ++a) {  // a 是行方向增量，取 -1、0、1
            for (int b = -1; b <= 1; ++b) {  // b 是列方向增量，取 -1、0、1
                if (a == 0 && b == 0) {  // (0, 0) 表示原地不动，不是一个方向
                    continue;  // 跳过原地，只处理八个真实方向
                }
                int i = rMove, j = cMove;  // 从落子点出发，沿当前方向 (a, b) 逐步前进
                int cnt = 0;  // 记录本方向已经走过的格子数
                while (0 <= i + a && i + a < 8 && 0 <= j + b && j + b < 8) {  // 只要下一格仍在棋盘范围内就继续探测
                    i += a;  // 行坐标前进一格
                    j += b;  // 列坐标前进一格
                    if (++cnt > 1 && board[i][j] == color) {  // 先走再计数：跳过紧邻的一格，若之后遇到同色棋子，说明中间夹着对方棋子
                        return true;  // 该方向合法，整体判定为合法并立即返回
                    }
                    if (board[i][j] == color || board[i][j] == '.') {  // 遇到我方棋子或空位（且中间没有可夹的对方棋子），本方向中断
                        break;  // 换下一个方向继续检查
                    }
                }
            }
        }
        return false;  // 八个方向都无法夹子，操作不合法
    }
};