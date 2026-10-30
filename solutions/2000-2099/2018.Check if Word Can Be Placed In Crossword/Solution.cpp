// 题目：2018. 判断单词是否能放入填字游戏内（Check if Word Can Be Placed In Crossword）
// 思路：枚举每个格子作为起点，只接受左侧（或上方）紧邻边界或障碍的位置；再用 lambda check 沿四个方向逐字符匹配，并要求单词末尾之后的那一格不是普通字母。
// 时间复杂度：O(m * n * k)，每个起点最多四个方向、每个方向校验 k 个字符；空间复杂度：O(1)，只用常数个扫描变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {  // board：填字棋盘（' ' 为空格，'#' 为障碍）；word：待放置的单词
        int m = board.size(), n = board[0].size();  // m 行 n 列（题面保证棋盘非空）
        int k = word.size();  // 单词长度，四个方向都要正好走 k 步
        auto check = [&](int i, int j, int a, int b) {  // 从 (i, j) 沿方向 (a, b) 试放；引用捕获 m、n、k、board、word
            int x = i + a * k, y = j + b * k;  // 单词末尾之后的下一格坐标
            if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] != '#') {  // 末尾之后还是普通字母，说明这一段被更长的连续字母段占据，放不下
                return false;  // 该方向不可行
            }  // 末尾检查结束
            for (char& c : word) {  // 把单词字符逐个对齐到棋盘
                if (i < 0 || i >= m || j < 0 || j >= n || (board[i][j] != ' ' && board[i][j] != c)) {  // 越界、撞障碍、或该格是别的字母，都判失败
                    return false;  // 匹配失败
                }  // 越界与字符冲突判断结束
                i += a;  // 行坐标沿方向前进一格
                j += b;  // 列坐标沿方向前进一格
            }  // 单词字符遍历结束
            return true;  // 全部字符都匹配，说明可以这样放
        };  // check lambda 定义结束
        for (int i = 0; i < m; ++i) {  // 枚举起点行
            for (int j = 0; j < n; ++j) {  // 枚举起点列
                bool leftToRight = (j == 0 || board[i][j - 1] == '#') && check(i, j, 0, 1);  // 从左往右：左侧必须是边界或障碍，才算这一横段的起点
                bool rightToLeft = (j == n - 1 || board[i][j + 1] == '#') && check(i, j, 0, -1);  // 从右往左：右侧必须是边界或障碍
                bool upToDown = (i == 0 || board[i - 1][j] == '#') && check(i, j, 1, 0);  // 从上往下：上方必须是边界或障碍
                bool downToUp = (i == m - 1 || board[i + 1][j] == '#') && check(i, j, -1, 0);  // 从下往上：下方必须是边界或障碍
                if (leftToRight || rightToLeft || upToDown || downToUp) {  // 任一方向成立即可放入
                    return true;  // 找到可行方案，直接返回
                }  // 判断结束
            }  // 起点列枚举结束
        }  // 起点行枚举结束
        return false;  // 所有起点与方向都试过，仍然放不下
    }  // placeWordInCrossword 方法结束
};  // Solution 类定义结束