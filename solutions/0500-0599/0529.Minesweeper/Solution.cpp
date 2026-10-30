// 题目：529. 扫雷游戏（Minesweeper）
// 思路：DFS 洪水填充。点到地雷直接改成 X；否则统计周围 8 格的地雷数，为 0 才继续向外扩散。
// 时间复杂度：O(m*n)，每个格子至多被访问一次；空间复杂度：O(m*n)，递归栈最坏深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {  // board 是棋盘，click 是点击坐标
        int m = board.size(), n = board[0].size();  // m 行 n 列，后面判越界要用
        int i = click[0], j = click[1];  // 把点击坐标拆成行列

        function<void(int, int)> dfs = [&](int i, int j) {  // 递归函数：处理格子 (i,j)，按引用捕获 m、n、board
            int cnt = 0;  // 统计周围 8 格里的地雷数
            for (int x = i - 1; x <= i + 1; ++x) {  // 枚举行偏移 -1、0、1
                for (int y = j - 1; y <= j + 1; ++y) {  // 枚举列偏移 -1、0、1
                    if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'M') {  // 先判越界，再看是不是未引爆地雷
                        ++cnt;  // 地雷计数加一（自身格此时是 E，不会被算进去）
                    }
                }
            }
            if (cnt) {  // 周围有地雷，停止扩散
                board[i][j] = cnt + '0';  // 用字符写入地雷数，题目要求只写这一个字符
            } else {  // 周围没有地雷，把本格标为 B 并继续扩散
                board[i][j] = 'B';  // B 表示已挖开的空白格
                for (int x = i - 1; x <= i + 1; ++x) {  // 再枚举一遍 8 邻域
                    for (int y = j - 1; y <= j + 1; ++y) {  // 同上
                        if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'E') {  // 只递归尚未挖开的空格 E
                            dfs(x, y);  // 递归挖开相邻空格
                        }
                    }
                }
            }
        };

        if (board[i][j] == 'M') {  // 第一次点击就踩到地雷
            board[i][j] = 'X';  // 直接引爆，游戏结束，不再递归
        } else {  // 点到的不是地雷
            dfs(i, j);  // 从点击位置开始挖开
        }
        return board;  // 返回更新后的棋盘
    }
};