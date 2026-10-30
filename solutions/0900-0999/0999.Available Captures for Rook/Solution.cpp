// 题目：999. 可以被一步捕获的棋子数（Available Captures for Rook）
// 思路：先找到白车 R，再沿上下左右四个方向逐格前进，遇到边界或黑象 B 就停；遇到第一个黑卒 p 则计数加一，同一方向最多吃一个。
// 时间复杂度：O(n^2)，n = 8 为棋盘边长；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numRookCaptures(vector<vector<char>>& board) {  // board：8×8 棋盘，返回白车一步内能吃掉的黑卒数量
        const int dirs[5] = {-1, 0, 1, 0, -1};  // 方向增量数组：上、右、下、左，末尾多一个 -1 便于用 dirs[k] 与 dirs[k+1] 成对取出行列增量
        int n = board.size();  // 棋盘边长（题目固定 8，这里按通用写法取）
        for (int i = 0; i < n; ++i) {  // 枚举行下标
            for (int j = 0; j < n; ++j) {  // 枚举列下标
                if (board[i][j] == 'R') {  // 找到白车 R 的位置
                    int ans = 0;  // 答案计数器：四个方向最多各吃一个子
                    for (int k = 0; k < 4; ++k) {  // 依次尝试四个方向
                        int x = i + dirs[k], y = j + dirs[k + 1];  // 计算该方向上的下一个格子坐标
                        while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] != 'B') {  // 不出界、且没有被黑象 B 挡住时，才继续沿该方向前进
                            if (board[x][y] == 'p') {  // 遇到黑卒 p
                                ++ans;  // 可以吃掉一个子，计数加一
                                break;  // 同一方向最多吃一个，立即结束该方向的扫描
                            }
                            x += dirs[k];  // 沿当前方向再前进一行
                            y += dirs[k + 1];  // 列坐标同步前进
                        }
                    }
                    return ans;  // 车只有一个，找到后直接返回统计结果
                }
            }
        }
        return 0;  // 保底返回：棋盘上一定存在 R，这里只是兜底
    }
};
