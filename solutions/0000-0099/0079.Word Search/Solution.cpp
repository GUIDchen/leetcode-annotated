// 题目：79. 单词搜索（Word Search）
// 思路：网格 DFS 回溯。从每个格子出发尝试匹配 word，匹配到某一位后用临时标记 '0' 封住已用格子防止重复经过，四个方向递归，失败则恢复原字符。
// 时间复杂度：O(m * n * 3^L)，L 为单词长度，每个起点最多向三个方向继续；空间复杂度：O(L)，递归栈深度为单词长度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool exist(vector<vector<char>>& board, string word) {  // board 是字符网格，word 是待匹配的单词
        int m = board.size(), n = board[0].size();  // m 是行数，n 是列数，用于边界判断
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两两配对得到上、右、下、左四个方向的偏移量
        function<bool(int, int, int)> dfs = [&](int i, int j, int k) -> bool {  // 递归 lambda：从 (i, j) 出发匹配 word[k...]，[&] 按引用捕获
            if (k == word.size() - 1) {  // 已经匹配到单词的最后一个字符，无需再向四周扩展
                return board[i][j] == word[k];  // 当前格子是否正好等于最后一个字符
            }
            if (board[i][j] != word[k]) {  // 当前格子的字符和要匹配的字符不同
                return false;  // 这个方向走不通，立即回溯
            }
            char c = board[i][j];  // 先暂存当前格子的原字符，回溯时要还原
            board[i][j] = '0';  // 用 '0' 标记为「已使用」，防止同一条路径重复经过同一个格子
            for (int u = 0; u < 4; ++u) {  // 依次尝试上、右、下、左四个方向
                int x = i + dirs[u], y = j + dirs[u + 1];  // 由相邻两个偏移量算出下一个格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] != '0' && dfs(x, y, k + 1)) {  // 越界、已使用、递归失败都算走不通
                    return true;  // 四个条件全部满足说明找到完整路径，直接返回成功
                }
            }
            board[i][j] = c;  // 四个方向都失败，恢复原字符，让其他搜索路径还能使用这个格子
            return false;  // 以 (i, j) 为起点匹配 word[k...] 失败
        };
        for (int i = 0; i < m; ++i) {  // 枚举所有可能的起点行
            for (int j = 0; j < n; ++j) {  // 枚举所有可能的起点列
                if (dfs(i, j, 0)) {  // 从 (i, j) 出发尝试匹配整个单词
                    return true;  // 任意一个起点成功即可返回 true
                }
            }
        }
        return false;  // 所有起点都失败，说明网格里不存在这个单词
    }
};