// 题目：723. 粉碎糖果（Candy Crush，会员题）
// 思路：直接模拟。每轮先扫描水平/竖直三连并用负数标记待消除（标记而不立即清零，避免同一轮重复判断），再让每列糖果下落，直到没有可消除的为止。
// 时间复杂度：O(m*n*(m+n))（轮数与棋盘同阶，每轮 O(m*n)）；空间复杂度：O(1)（原地修改，不计返回值）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {  // board：糖果棋盘，0 表示空位
        int m = board.size(), n = board[0].size();  // 行数 m 与列数 n
        bool run = true;  // 本轮是否发生过消除（有变化就还要继续模拟）
        while (run) {  // 反复执行「标记 → 下落」直到棋盘稳定
            run = false;  // 先假设本轮不会消除
            for (int i = 0; i < m; ++i) {  // 按行扫描水平方向的三连
                for (int j = 0; j < n - 2; ++j) {  // 枚举连续的三列
                    if (board[i][j] != 0 && abs(board[i][j]) == abs(board[i][j + 1]) && abs(board[i][j]) == abs(board[i][j + 2])) {  // 非空且三个相邻格子值相同（abs 兼容已经被标记成负数的格子）
                        run = true;  // 记录本轮发生了消除
                        board[i][j] = board[i][j + 1] = board[i][j + 2] = -abs(board[i][j]);  // 取负值作标记表示待消除；先标记不清零，避免影响本轮后续判断
                    }  // if 结束
                }  // 内层 for 结束
            }  // 外层 for 结束
            for (int j = 0; j < n; ++j) {  // 按列扫描竖直方向的三连
                for (int i = 0; i < m - 2; ++i) {  // 枚举连续的三行
                    if (board[i][j] != 0 && abs(board[i][j]) == abs(board[i + 1][j]) && abs(board[i][j]) == abs(board[i + 2][j])) {  // 同列相邻三格值相同（abs 兼容负标记）
                        run = true;  // 记录本轮发生了消除
                        board[i][j] = board[i + 1][j] = board[i + 2][j] = -abs(board[i][j]);  // 取负值标记待消除
                    }  // if 结束
                }  // 内层 for 结束
            }  // 外层 for 结束
            if (run) {  // 本轮有消除，需要整理下落
                for (int j = 0; j < n; ++j) {  // 逐列处理糖果下落
                    int curr = m - 1;  // curr 指向当前最低的空位
                    for (int i = m - 1; i >= 0; --i) {  // 自底向上遍历该列
                        if (board[i][j] > 0) {  // 正数才是未被消除的糖果（负数代表待消除）
                            board[curr][j] = board[i][j];  // 把糖果放到当前最低的空位上
                            --curr;  // 放置位置上移一格
                        }  // if 结束
                    }  // 构建列结束
                    while (curr > -1) {  // 剩余的上方位置全部置空
                        board[curr][j] = 0;  // 置 0 表示空位
                        --curr;  // 继续向上清空
                    }  // while 结束
                }  // for 结束
            }  // if 结束
        }  // while 结束：棋盘已稳定
        return board;  // 返回稳定后的棋盘
    }  // 方法结束
};  // 类定义结束