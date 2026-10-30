// 题目：348. 设计井字棋（Design Tic-Tac-Toe）
// 思路：不保存 n×n 的棋盘，而是给每个玩家维护「每行 / 每列 / 两条对角线」上的棋子计数；某条线的计数达到 n 就说明该玩家连成 n 子获胜。
// 时间复杂度：move 为 O(1)；空间复杂度：O(n)，每个玩家 2n+2 个计数器。
class TicTacToe {  // 井字棋类
private:  // 私有成员只供内部使用
    int n;  // 棋盘边长 n，获胜需要一条线上有 n 个同色棋子
    vector<vector<int>> cnt;  // cnt[玩家][线编号] 记录该玩家在某条线上的棋子数；线编号约定见 move 方法

public:  // 对外接口可见
    TicTacToe(int n)  // 构造函数：n 为棋盘边长
        : n(n)  // 初始化成员 n（冒号左边是成员，右边是形参，同名时靠这个区分）
        , cnt(2, vector<int>((n << 1) + 2, 0)) {  // 两个玩家各一组计数器，每组 n 行 + n 列 + 2 条对角线，初值全 0
    }  // 构造函数体为空，初始化列表已完成全部工作

    int move(int row, int col, int player) {  // row、col：落子坐标；player 取 1 或 2；返回获胜玩家编号，暂时无人获胜返回 0
        vector<int>& cur = cnt[player - 1];  // 取出当前玩家对应的计数数组（下标 player-1 映射到 0/1）
        ++cur[row];  // 该行棋子数加一：行编号直接占下标 0..n-1
        ++cur[n + col];  // 该列棋子数加一：列编号偏移 n 后占下标 n..2n-1
        if (row == col) {  // 落在主对角线上（行列下标相等）才累加
            ++cur[n << 1];  // 主对角线计数加一，线编号为 2n（即 n << 1）
        }  // if 结束
        if (row + col == n - 1) {  // 落在副对角线上（行列下标之和为 n-1）才累加
            ++cur[n << 1 | 1];  // 副对角线计数加一，线编号为 2n+1（即 n << 1 | 1）
        }  // if 结束
        if (cur[row] == n || cur[n + col] == n || cur[n << 1] == n || cur[n << 1 | 1] == n) {  // 四条经过本次落子的线里只要有一条计满 n 个，就说明当前玩家获胜
            return player;  // 返回获胜玩家编号
        }  // if 结束
        return 0;  // 没有任何一条线被填满，游戏继续
    }  // move 方法结束
};  // 类定义结束

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */