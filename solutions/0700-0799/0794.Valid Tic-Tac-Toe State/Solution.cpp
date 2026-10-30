// 题目：794. 有效的井字游戏（Valid Tic-Tac-Toe State）
// 思路：合法局面只需满足三条：X 先手所以 X 数等于 O 数或比 O 多 1；X 赢时必须刚下完（X 比 O 多 1）；O 赢时数量必须相等。扫盘统计与判三连即可。
// 时间复杂度：O(1)，棋盘固定 3x3；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validTicTacToe(vector<string>& board) {  // board：3x3 棋盘，字符为 'X'、'O' 或空格
        auto count = [&](char x) {  // count(x)：统计棋盘中字符 x 的落子数
            int ans = 0;  // 计数器
            for (auto& row : board)  // 逐行遍历
                for (auto& c : row) ans += c == x;  // 逐格比较，相等时布尔值转为 1 累加
            return ans;  // 返回该字符的总个数
        };  // count 结束
        auto win = [&](char x) {  // win(x)：判断字符 x 是否已经连成三子
            for (int i = 0; i < 3; ++i) {  // 依次检查第 i 行与第 i 列
                if (board[i][0] == x && board[i][1] == x && board[i][2] == x) return true;  // 整行都是 x
                if (board[0][i] == x && board[1][i] == x && board[2][i] == x) return true;  // 整列都是 x
            }  // 行列检查结束
            if (board[0][0] == x && board[1][1] == x && board[2][2] == x) return true;  // 主对角线全为 x
            return board[0][2] == x && board[1][1] == x && board[2][0] == x;  // 副对角线全为 x 则赢，否则没连成
        };  // win 结束
        int x = count('X'), o = count('O');  // 统计双方落子数
        if (x != o && x - 1 != o) return false;  // X 先手：X 的个数只能等于 O，或恰好比 O 多 1
        if (win('X') && x - 1 != o) return false;  // X 赢说明最后一步是 X 下的，此时 X 必须比 O 多 1
        return !(win('O') && x != o);  // O 赢时双方数量必须相等；返回真表示其余情况都合法
    }  // validTicTacToe 结束
};  // 类定义结束